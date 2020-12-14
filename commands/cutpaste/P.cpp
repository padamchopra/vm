#include "P.h"
#include "../../model/VMModel.h"
#include "../../mode/NormalMode.h"

VM::P::P() {
    beforeCursor = false;
    commandSequence.push_back('p');
}

void VM::P::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    auto *mode = dynamic_cast<NormalMode*>(model.getMode(NORMAL_MODE));
    if (mode != nullptr) {
        std::pair<InteractionType, std::vector<std::string>> clipboard = mode->getClipBoard();
        std::vector<std::string> lines = clipboard.second;
        //pre process cursor
        std::pair<int, int> cursor = state->getCursor();
        int offset = state->getOffset();
        int totalLines = state->getTotalLines();

        while (times > 0) {
            if (clipboard.first == ALL) {
                executeOnceForAll(model, lines);
            } else {
                executeOnceForLine(model, lines);
            }
            --times;
        }

        if (clipboard.first == LINE) {
            if (beforeCursor) {
                int totalLinesNow = state->getTotalLines();
                while (totalLinesNow - totalLines > 1) {
                    state->moveCursor(DOWN, model.getController());
                    ++totalLines;
                }
            } else {
                state->setCursor({cursor.first, 0});
                state->setOffset(offset);
                state->moveCursor(DOWN, model.getController());
            }
        }
        state->revalidateCursorForLine();
    }
}

void VM::P::executeOnceForLine(VM::VMModel &model, const std::vector<std::string> &lines) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    state->setCursor({cursor.first, 0});
    if (beforeCursor) {
        if (cursor.first == 0) state->addLine(0, "");
        state->moveCursor(UP, model.getController());
    }
    for (const auto& line: lines) {
        state->addLine(state->getCursor().first + 1, line);
        state->moveCursor(DOWN, model.getController());
    }
    if (beforeCursor && cursor.first == 0) {
        state->moveCursor(UP, model.getController());
        state->removeLine(0);
    }
}

void VM::P::executeOnceForAll(VM::VMModel &model, const std::vector<std::string> &lines) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor =state->getCursor();
    if (cursor.second != 0) ++cursor.second;
    state->setCursor(cursor);
    std::string remainingFirstLine;
    std::string firstLine = state->getLine(cursor.first);
    if (firstLine.empty()) {
        firstLine = "";
        remainingFirstLine = "";
    } else if (cursor.second == 0) {
        if (beforeCursor) {
            remainingFirstLine = firstLine;
            firstLine = "";
        } else {
            remainingFirstLine = firstLine.substr(1);
            firstLine = firstLine.substr(0, 1);
        }
    } else if (cursor.second == (int) firstLine.length() - 1){
        if (beforeCursor) {
            remainingFirstLine = firstLine.substr(firstLine.length() - 1);
            firstLine = firstLine.substr(0, firstLine.length() - 1);
        } else {
            remainingFirstLine = "";
        }
    } else {
        if (beforeCursor) {
            remainingFirstLine = firstLine.substr(cursor.second - 1);
            firstLine = firstLine.substr(0, cursor.second - 1);
        } else {
            remainingFirstLine = firstLine.substr(cursor.second);
            firstLine = firstLine.substr(0, cursor.second);
        }
    }

    if (lines.size() == 1) {
        state->setLine(cursor.first, firstLine + lines.at(0) + remainingFirstLine);
    } else {
        state->setLine(cursor.first, firstLine + lines.at(0));
        state->setCursor({cursor.first, 0});
        for (int i = 1; i < (int) lines.size() - 1; ++i) { //leave last line
            state->addLine(state->getCursor().first + 1, lines.at(i));
            state->moveCursor(DOWN, model.getController());
        }
        state->addLine(state->getCursor().first + 1, lines.back() + remainingFirstLine);
        state->moveCursor(DOWN, model.getController());
    }
    cursor = state->getCursor();
    int toAdd = lines.back().length();
    toAdd = toAdd == 0 ? toAdd : toAdd - 1;
    state->setCursor({cursor.first, cursor.second + toAdd});
    state->revalidateCursorForLine();
}

VM::P::P(bool canUndo, bool before): P{} {
    undoable = canUndo;
    beforeCursor = before;
}
