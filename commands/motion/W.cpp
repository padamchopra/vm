#include "W.h"
#include "../../model/VMModel.h"

VM::W::W() {
    commandSequence.push_back('w');
}

void VM::W::executeFor(VM::VMModel &model, int times) {
    while (times > 0) {
        bool didChange = executeOnce(model);
        if (!didChange) {
            WindowState *state = model.getActiveState();
            std::pair<int, int> cursor = state->getCursor();
            const std::string& line = state->getLine(cursor.first);
            if (line.length() == 0) {
                cursor.second = 0;
            } else {
                cursor.second = line.length() - 1;
            }
            model.getActiveState()->setCursor(cursor);
            break;
        }
        --times;
    }
}

bool VM::W::executeOnce(VM::VMModel &model) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    std::string line = state->getLine(cursor.first);
    int pos = cursor.second + line.substr(cursor.second).find(' ');
    if (pos == cursor.second + std::string::npos || pos == line.length() - 1) { //not found or last char is ' '
        if (cursor.first != state->getTotalLines() - 1) { //if not last line, move to next line and search again
            state->moveCursor(DOWN, model.getController());
            cursor = state->getCursor();
            cursor.second = 0;
            state->setCursor(cursor);
            std::string nextLine = state->getLine(cursor.first);
            if (nextLine.empty() || nextLine.at(0) == ' ') {
                return executeOnce(model);
            }
            return true;
        }
        return false;
    } else {
        state->setCursor({cursor.first, pos + 1});
        return true;
    }
}
