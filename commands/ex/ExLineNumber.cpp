#include "ExLineNumber.h"
#include "../../model/VMModel.h"

bool VM::ExLineNumber::isAMatch(const std::vector<int> &inputSequence) {
    if (inputSequence.size() <= 1) {
        return false;
    }
    for (int i = 0; i < (int) inputSequence.size() - 1; ++i) {
        if (!isdigit((char) inputSequence.at(i))) {
            return false;
        }
    }
    return true;
}

VM::ExLineNumber::ExLineNumber() = default;

void VM::ExLineNumber::executeFor(VM::VMModel &model, const std::string &inputSequence) {
    WindowState *state = model.getActiveState();
    int lineNumber = 0;
    try {
        lineNumber = std::stoi(inputSequence);
    } catch (...) {
        model.updateStatusWithError("Unable to move to specified line");
        return;
    }
    if (lineNumber > state->getTotalLines()) {
        lineNumber = state->getTotalLines();
    }
    if (lineNumber != 0) {
        --lineNumber;
    }

    if (state->getTotalLines() == 1) {
        state->setCursor({0,0});
        state->setOffset(0);
    } else {
        int additive = 1;
        std::pair<int, int> cursor = state->getCursor();
        cursor.second = 0;
        state->setCursor(cursor);
        if (lineNumber < cursor.first) {
            additive = -1;
        }
        while (state->getCursor().first != lineNumber) {
            if (additive == 1) {
                state->moveCursor(DOWN, model.getController());
            } else {
                state->moveCursor(UP, model.getController());
            }
        }
    }
}
