#include "ControlU.h"
#include "../../model/VMModel.h"
#include "ControlB.h"

VM::ControlU::ControlU() {
    commandSequence.push_back(CTRL_U);
}

void VM::ControlU::executeFor(VM::VMModel &model, int times) {
    while (times > 0) {
        executeOnce(model);
        --times;
    }
}

void VM::ControlU::executeOnce(VM::VMModel &model) {
    WindowState *state = model.getActiveState();
    int prevOffset = state->getOffset();
    ControlB b{};
    b.execute(model, 1);
    int newOffset = state->getOffset();
    if (newOffset != prevOffset) {
        newOffset = (prevOffset + newOffset)/2;
        state->setOffset(newOffset);
        state->setCursor({newOffset, 0});
    }
}
