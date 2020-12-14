#include "CapI.h"
#include "../../model/VMModel.h"
#include "I.h"

VM::CapI::CapI() {
    commandSequence.push_back('I');
}

void VM::CapI::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    state->setCursor({state->getCursor().first, 0});
    I i{false};
    i.execute(model, times);
}
