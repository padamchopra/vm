#include "CapA.h"
#include "../../model/VMModel.h"
#include "A.h"

VM::CapA::CapA() {
    commandSequence.emplace_back('A');
}

void VM::CapA::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    int lineLength = state->getLine(cursor.first).length();
    if (lineLength != 0) {
        cursor.second = lineLength - 1;
        state->setCursor(cursor);
    }
    A a{false};
    a.execute(model, times);
}
