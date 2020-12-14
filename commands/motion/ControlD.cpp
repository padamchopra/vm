#include "ControlD.h"
#include "../../model/VMModel.h"
#include "ControlF.h"

VM::ControlD::ControlD() {
    commandSequence.push_back(CTRL_D);
}

void VM::ControlD::executeFor(VM::VMModel &model, int times) {
    while (times > 0) {
        executeOnce(model);
        --times;
    }
}

void VM::ControlD::executeOnce(VM::VMModel &model) {
    WindowState *state = model.getActiveState();
    int prevOffset = state->getOffset();
    ControlF f{};
    f.execute(model, 1);
    int newOffset = state->getOffset();
    if (newOffset != prevOffset) {
        newOffset = (newOffset + prevOffset)/2;
        state->setOffset(newOffset);
        state->setCursor({newOffset, 0});
    }
}
