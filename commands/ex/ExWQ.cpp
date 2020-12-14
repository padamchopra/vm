#include "ExWQ.h"
#include "../../model/VMModel.h"

VM::ExWQ::ExWQ() {
    commandSequence.push_back('w');
    commandSequence.push_back('q');
}

void VM::ExWQ::executeFor(VM::VMModel &model, const std::string &inputSequence) {
    WindowState *state = model.getActiveState();
    std::string newFileName;
    for (size_t i = 2; i < inputSequence.length(); ++i) {
        if (inputSequence.at(i) != ' ') {
            newFileName = inputSequence.substr(i);
            break;
        }
    }
    if (newFileName.empty()) {
        newFileName = state->getFileName();
    }
    if (newFileName.empty()) {
        model.updateStatusWithError("No file name");
    } else {
        state->saveFile(newFileName);
        std::pair<int, int> info = state->getFileInfo();
        std::string message = "\"" + newFileName + "\"" + " ";
        message += std::to_string(info.first) + "L, " + std::to_string(info.second) + "C written";
        model.updateStatus(message);
        model.stop();
    }
}
