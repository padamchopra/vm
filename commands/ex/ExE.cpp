#include "ExE.h"
#include "../../model/VMModel.h"

void VM::ExE::executeFor(VM::VMModel &model, const std::string &inputSequence) {
    std::string newFileName;
    for (size_t i = 2; i < inputSequence.length(); ++i) {
        if (inputSequence.at(i) != ' ') {
            newFileName = inputSequence.substr(i);
            break;
        }
    }
    if (newFileName.empty()) {
        model.addState("");
        model.updateStatusWithError("loaded empty file buffer in next tab");
    } else {
        model.addState(newFileName);
        model.updateStatus("loaded file "+ newFileName + " in next tab");
    }
}

VM::ExE::ExE() {
    commandSequence.push_back('e');
}
