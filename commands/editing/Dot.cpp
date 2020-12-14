#include "Dot.h"
#include "../../model/VMModel.h"
#include "../../mode/NormalMode.h"
#include "../insert/InsertCommand.h"
#include "../../mode/InsertMode.h"

void VM::Dot::executeFor(VM::VMModel &model, int times) {
    auto *mode = dynamic_cast<NormalMode*>(model.getMode(NORMAL_MODE));
    if (mode != nullptr) {
        auto *command = dynamic_cast<InsertCommand*>(mode->getLastCommandRun());
        if (command == nullptr) {
            std::vector<int> lastInputSequence = mode->getLastInputSequenceBeforeCommandRun();
            mode->simulateInputSequence(lastInputSequence, times);
        } else {
            auto *imode = dynamic_cast<InsertMode*>(model.getMode(INSERT_MODE));
            if (imode != nullptr) {
                std::vector<int> sequence = imode->getSequence();
                command->execute(model, 1);
                imode->makeExitPreparations();
                imode->setSequence(sequence);
                imode->setCountForCall(times+1);
                imode->executeRecordedSequence();
            }

        }
    }
}

VM::Dot::Dot() {
    undoable = false;
    dottable = false;
    commandSequence.push_back('.');
}
