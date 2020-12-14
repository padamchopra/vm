#include "ExR.h"
#include "../../model/VMModel.h"
#include "../../utility/FileManager.h"

VM::ExR::ExR() {
    commandSequence.push_back('r');
}

void VM::ExR::executeFor(VM::VMModel &model, const std::string &inputSequence) {
    WindowState *state = model.getActiveState();
    std::string newFileName;
    for (size_t i = 2; i < inputSequence.length(); ++i) {
        if (inputSequence.at(i) != ' ') {
            newFileName = inputSequence.substr(i);
            break;
        }
    }
    std::vector<std::string> lines;
    if (newFileName.empty()) {
        lines = state->getLines();
    } else {
        try {
            lines = FileManager::readFromFile(newFileName);
        } catch (...) {
            model.updateStatusWithError("Can't open file " + newFileName);
            return;
        }
    }
    state->memoriseState(model.getController());
    std::pair<int, int> cursor = state->getCursor();
    for (const auto& line: lines) {
        state->addLine(cursor.first + 1, line);
        ++cursor.first;
    }
    state->moveCursor(DOWN, model.getController());
    model.updateStatus("");
}
