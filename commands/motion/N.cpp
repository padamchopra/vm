#include "N.h"
#include "../../model/VMModel.h"
#include "../../utility/FileManager.h"

VM::N::N() {
    flip = false;
    direction = 1;
    commandSequence.push_back('n');
}

void VM::N::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    if (!searchFor.empty()) {
        bool exists = doesPhraseEvenExist(state);
        if (!exists) {
            errorOccured = true;
            statusBarOutput = "Substring not found: " + searchFor;
        } else {
            while (times > 0) {
                executeOnce(model, direction);
                --times;
            }
            errorOccured = false;
            statusBarOutput = "/" + searchFor;
        }
    } else {
        errorOccured = true;
        statusBarOutput = "Invalid search history. Search using /.";
    }
}

void VM::N::execute(VM::VMModel &model, int times) {
    statusBarOutput = "";
    errorOccured = false;
    try {
        std::vector<std::string> lines = FileManager::readFromFile(FileManager::searchFile);
        searchFor = lines.at(0);
        int d = std::stoi(searchFor.substr(0, 1));
        if (d == BACKWARD) {
            direction = -1;
        } else {
            direction = 1;
        }

        if (flip) {
            direction = direction == -1 ? 1 : -1;
        }

        searchFor = searchFor.substr(1);
        Command::execute(model, times);
        if (errorOccured) {
            model.updateStatusWithError(statusBarOutput);
        } else {
            model.updateStatus(statusBarOutput);
        }
    } catch (...) {
        //file doesn't exist nothing has been searched till today
        model.updateStatusWithError("No search history. Search using / command.");
    }
}

void VM::N::executeOnce(VMModel &model, int colOffset) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    size_t found;
    if (direction == 1) {
        found = state->getLine(cursor.first).find(searchFor, cursor.second + colOffset);
    } else {
        if (cursor.second != 0) {
            found = state->getLine(cursor.first).rfind(searchFor, cursor.second + colOffset);
        } else {
            found = std::string::npos;
        }
    }
    if (found != std::string::npos) {
        cursor.second = found;
        state->setCursor(cursor);
    } else {
        if (cursor.first >= state->getTotalLines() - 1 && direction == 1) {
            state->setCursor(std::pair<int, int>(0, 0));
            state->setOffset(0);
        } else if (cursor.first == 0 && direction == -1) {
            while (state->getCursor().first != state->getTotalLines() - 1) {
                state->moveCursor(DOWN, model.getController());
            }
            std::pair<int, int> temp = state->getCursor();
            int lineLength = state->getLine(temp.first).length();
            temp.second = lineLength == 0 ? 0 : lineLength - 1;
            state->setCursor(temp);
        } else {
            if (direction == 1) {
                state->moveCursor(DOWN, model.getController());
                state->setCursor(std::pair<int, int>(state->getCursor().first, 0));
            } else {
                state->moveCursor(UP, model.getController());
                std::pair<int, int> temp = state->getCursor();
                int lineLength = state->getLine(temp.first).length();
                temp.second = lineLength == 0 ? 0 : lineLength - 1;
                state->setCursor(temp);
            }
        }
        executeOnce(model, 0);
    }
}

bool VM::N::doesPhraseEvenExist(VM::WindowState *state) {
    for (int i = 0; i < state->getTotalLines(); ++i) {
        if (state->getLine(i).find(searchFor) != std::string::npos) {
            return true;
        }
    }
    return false;
}

VM::N::N(bool flipDirection): N{} {
    flip = flipDirection;
}
