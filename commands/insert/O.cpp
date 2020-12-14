#include "O.h"
#include "../../model/VMModel.h"
#include "A.h"
#include "../../mode/InsertMode.h"

VM::O::O() {
    commandSequence.push_back('o');
}

void VM::O::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    state->addLine(cursor.first + 1, "");
    state->moveCursor(DOWN, model.getController());
    state->revalidateCursorForLine();
    auto *mode = dynamic_cast<InsertMode*>(model.getMode(INSERT_MODE));
    if (mode != nullptr) {
        mode->setEnterAtEnd(true);
    }
    A a{false};
    a.execute(model, times);
}

