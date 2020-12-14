#include "Dollar.h"
#include "../../model/VMModel.h"

VM::Dollar::Dollar() {
    commandSequence.push_back('$');
}

void VM::Dollar::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    --times;
    cursor.first += times;
    if (cursor.first >= state->getTotalLines()) {
        cursor.first = state->getTotalLines() - 1;
    }
    int length = state->getLine(cursor.first).length();
    if (length != 0) --length;
    state->setCursor({cursor.first, length});
}
