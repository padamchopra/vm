#include "CapF.h"
#include "../../model/VMModel.h"
#include "../../mode/NormalMode.h"

VM::CapF::CapF() {
    lookFor = '\0';
    commandSequence.push_back('F');
}

void VM::CapF::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    int newColumn = cursor.second - 1;
    std::string line = state->getLine(cursor.first);
    char c;
    if (lookFor == '\0') {
        c = model.getInput().back();
        auto *mode = dynamic_cast<NormalMode*>(model.getMode(NORMAL_MODE));
        if (mode != nullptr) mode->setLastFInfo({false, c});
    } else {
        c = lookFor;
    }

    for (; newColumn > 0 && times > 0; --newColumn) {
        if (line.at(newColumn) == c) {
            --times;
        }
    }

    if (times == 0) {
        state->setCursor(std::pair<int, int>(cursor.first, newColumn+1));
    }
}

VM::CapF::CapF(char look): CapF{} {
    lookFor = look;
}
