#include "U.h"
#include "../../model/VMModel.h"

VM::U::U() {
    undoable = false;
    commandSequence.push_back('u');
}

void VM::U::executeFor(VM::VMModel &model, int times) {
    std::string finalMessage = model.getActiveState()->previousState(times);
    model.updateStatus(finalMessage);
}
