#include "ExZero.h"
#include "../../model/VMModel.h"

VM::ExZero::ExZero() {
    commandSequence.push_back('0');
}

void VM::ExZero::executeFor(VM::VMModel &model, const std::string &inputSequence) {
    WindowState *state = model.getActiveState();
    state->setCursor({0,0});
    state->setOffset(0);
}
