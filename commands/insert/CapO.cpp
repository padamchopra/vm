#include "CapO.h"
#include "../../model/VMModel.h"
#include "A.h"
#include "../../mode/InsertMode.h"

VM::CapO::CapO() {
    commandSequence.push_back('O');
}

void VM::CapO::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    state->addLine(cursor.first, "");
    state->revalidateCursorForLine();
    auto *mode = dynamic_cast<InsertMode*>(model.getMode(INSERT_MODE));
    if (mode != nullptr) {
        mode->setEnterAtEnd(true);
    }
    A a{false};
    a.execute(model, times);
}
