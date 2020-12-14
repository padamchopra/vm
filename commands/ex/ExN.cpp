#include "ExN.h"
#include "../../model/VMModel.h"

VM::ExN::ExN() {
    commandSequence.push_back('n');
}

void VM::ExN::executeFor(VM::VMModel &model, const std::string &inputSequence) {
    model.setCurrentState(model.getCurrentState() + 1);
}
