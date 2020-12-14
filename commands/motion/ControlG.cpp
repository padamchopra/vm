#include "ControlG.h"
#include "../../model/VMModel.h"

void VM::ControlG::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::string message = "\"" + state->getFileName() + "\" ";
    std::pair<int, int> fileInfo = state->getFileInfo();
    message += std::to_string(fileInfo.first) + "L, " + std::to_string(fileInfo.second) + "C ";
    if (state->isOriginalFile()) {
        message += "[Original] ";
    } else {
        message += "[Modified] ";
    }
    int currentLine = state->getCursor().first + 1;
    int totalLines = state->getTotalLines();
    int percent = (currentLine * 100)/totalLines;
    message += "-- " + std::to_string(percent) + "% --";
    model.updateStatus(message);
}

VM::ControlG::ControlG() {
    countable = false;
    recordable = false;
    commandSequence.push_back(CTRL_G);
}
