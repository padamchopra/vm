#include "ExPrev.h"
#include "../../model/VMModel.h"

VM::ExPrev::ExPrev() {
    commandSequence.push_back('p');
    commandSequence.push_back('r');
    commandSequence.push_back('e');
    commandSequence.push_back('v');
}

void VM::ExPrev::executeFor(VM::VMModel &model, const std::string &inputSequence) {
    model.setCurrentState(model.getCurrentState() - 1);
}
