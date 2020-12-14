#include "InsertMode.h"
#include "../model/VMModel.h"

VM::InsertMode::InsertMode(VM::VMModel &model) : Mode(model), enterAtEnd{false}, replaceMode{false}, lastCalledWithCount{1} {}

void VM::InsertMode::parseInputSequence(const std::vector<int> &inputSequence) {
    int key = inputSequence.back();
    WindowState *state = model.getActiveState();
    sequence.push_back(key);
    makeChanges(key, false);
    model.updateView(state);
}

void VM::InsertMode::setCountForCall(int num) {
    lastCalledWithCount = num;
}

void VM::InsertMode::executeRecordedSequence() {
    int times = lastCalledWithCount;
    WindowState *state = model.getActiveState();
    while (times > 1) { //has already been executed once
        std::pair<int, int> cursor = state->getCursor();
        if (cursor.second != 0) ++cursor.second;
        state->setCursor(cursor);
        for(int i : sequence) {
            makeChanges(i, true);
        }
        --times;
    }
    model.updateView(state);
    model.clearInputSequence();
}

void VM::InsertMode::makeChanges(int key, bool calledFromILoop) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    if (key == RARROW) {
        int length = state->getLine(cursor.first).length();
        if (cursor.second >= length - 1) {
            state->setCursor(std::pair<int, int>(cursor.first, length));
        } else {
            state->moveCursor(RIGHT, model.getController());
        }
    } else if (key == LARROW) {
        state->moveCursor(LEFT, model.getController());
    } else if (key == UARROW) {
        state->moveCursor(UP, model.getController());
    } else if (key == DARROW) {
        state->moveCursor(DOWN, model.getController());
    } else {
        if (key == BACKSPACE) {
            handleBackspace();
        } else if (key == ENTER) {
            std::string line = state->getLine(cursor.first);
            std::string newLine = line.substr(cursor.second);
            line = line.substr(0, cursor.second);
            state->setLine(cursor.first, line);
            state->addLine(cursor.first+1, newLine);
            state->moveCursor(DOWN, model.getController());
            state->setCursor(std::pair<int, int>(state->getCursor().first, 0));
        } else if (key == ESC || key == CTRL_C) {
            state->revalidateCursorForLine();
            if (!calledFromILoop) {
                makeExitPreparations();
            }
        } else {
            handleCharacterPrint(key);
        }
    }
}

void VM::InsertMode::setEnterAtEnd(bool enter) {
    enterAtEnd = enter;
}

void VM::InsertMode::makeExitPreparations() {
    model.changeMode(NORMAL_MODE);
    if (enterAtEnd) {
        sequence.insert(sequence.begin(), ENTER);
    }
    executeRecordedSequence();
    model.clearInputSequence();
    lastCalledWithCount = 1;
    enterAtEnd = false;
    replaceMode = false;
    model.updateStatus("");
}

void VM::InsertMode::setReplaceMode(bool replace) {
    replaceMode = replace;
}

void VM::InsertMode::handleBackspace() {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    std::string currentLine = state->getLine(cursor.first);
    if (cursor.second == 0 && cursor.first > 0) {
        if (replaceMode) {
            state->moveCursor(UP, model.getController());
            cursor = state->getCursor();
            int lineLength = state->getLine(cursor.first).length();
            state->setCursor({cursor.first, lineLength});
        } else {
            std::string newPreviousLine = state->getLine(cursor.first - 1);
            int previousLineLength = newPreviousLine.length();
            newPreviousLine =  newPreviousLine + currentLine;
            state->setLine(cursor.first - 1, newPreviousLine);
            state->moveCursor(UP, model.getController());
            while (previousLineLength > 0) {
                state->moveCursor(RIGHT, model.getController());
                --previousLineLength;
            }
            state->removeLine(cursor.first);
        }
    } else if (cursor.second > 0) {
        if (replaceMode) {
            state->moveCursor(LEFT, model.getController());
        } else {
            //backspacing just a character
            std::string newLine = state->getLine(cursor.first);
            state->moveCursor(LEFT, model.getController());
            state->setLine(cursor.first, newLine.erase(cursor.second-1, 1));
        }
    }
}

void VM::InsertMode::handleCharacterPrint(int key) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    char c = static_cast<char>(key);
    std::string line = state->getLine(cursor.first);
    if (line.empty()) {
        line = c;
    } else {
        if (cursor.second < (int) line.length()) {
            if (replaceMode) {
                std::string cInString;
                line.replace(cursor.second, 1, cInString + c);
            } else {
                line = line.substr(0, cursor.second) + c + line.substr(cursor.second);
            }
        } else {
            cursor.second = line.length();
            line = line + c;
        }
    }
    state->setLine(cursor.first, line);
    state->setCursor(std::pair<int, int>(cursor.first, cursor.second + 1));
}

const std::vector<int> &VM::InsertMode::getSequence() const {
    return sequence;
}

void VM::InsertMode::clearSequence() {
    sequence.clear();
}

void VM::InsertMode::setSequence(const std::vector<int> &s) {
    sequence = s;
}
