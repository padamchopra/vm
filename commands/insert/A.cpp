#include "A.h"
#include "I.h"
#include "../../model/VMModel.h"

VM::A::A() {
    commandSequence.push_back('a');
}

void VM::A::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    int lineLength = state->getLine(cursor.first).length();
    if (lineLength > 0) {
        state->setCursor(std::pair<int, int>(cursor.first, cursor.second + 1));
    }
    I i{false};
    i.execute(model, times);
}

VM::A::A(bool canUndo): A{} {
    undoable = canUndo;
}
