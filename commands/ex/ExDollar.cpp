#include "ExDollar.h"
#include "../../model/VMModel.h"

VM::ExDollar::ExDollar() {
    commandSequence.push_back('$');
}

void VM::ExDollar::executeFor(VM::VMModel &model, const std::string &inputSequence) {
    WindowState *state = model.getActiveState();
    if (state->getTotalLines() == 1) {
        state->setCursor({0,0});
        state->setOffset(0);
    } else {
        while (state->getCursor().first != state->getTotalLines() - 1) {
            state->moveCursor(DOWN, model.getController());
        }
    }
}
