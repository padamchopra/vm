#include "ExQ.h"
#include "../../model/VMModel.h"

VM::ExQ::ExQ() {
    commandSequence.push_back('q');
}

void VM::ExQ::executeFor(VM::VMModel &model, const std::string &inputSequence) {
    WindowState *state = model.getActiveState();
    if (state->isFileSaved()) {
        model.stop();
    } else {
        model.updateStatusWithError("No write since last change (add ! to override)");
    }
}
