#include "ExQExclamation.h"
#include "../../model/VMModel.h"

VM::ExQExclamation::ExQExclamation() {
    commandSequence.push_back('q');
    commandSequence.push_back('!');
}

void VM::ExQExclamation::executeFor(VM::VMModel &model, const std::string &inputSequence) {
    model.stop();
}
