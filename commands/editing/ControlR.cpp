#include "ControlR.h"
#include "../../model/VMModel.h"

void VM::ControlR::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::string message= state->redoState(times);
    model.updateStatus(message);
}

VM::ControlR::ControlR() {
    undoable = false;
    commandSequence.push_back(CTRL_R);
}
