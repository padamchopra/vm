#include "TerminalView.h"
#include <utility>

VM::TerminalView::TerminalView(std::shared_ptr<Terminal> terminal) : View{std::move(terminal)} {}

void VM::TerminalView::updateView(WindowState *state) {
    drawEmptyLines();
    int rowOffset = state->getOffset();
    std::pair<int, int> screenSize = terminal->getWindowSize(FILEWINDOW);
    std::pair<int, int> cursor = state->getCursor();
    std::string cursorInformation = "[" + std::to_string(cursor.first + 1) + ", " + std::to_string(cursor.second + 1) + "]";
    terminal->moveCursorInTerminal(STATUSBAR, {0, terminal->getWindowSize(STATUSBAR).second - cursorInformation.length() - 5});
    terminal->printString(STATUSBAR, cursorInformation);
    terminal->moveCursorInTerminal(FILEWINDOW, {0, 0});
    int rowsPrinted = 0;
    int row = rowOffset;
    bool didNotFit = false;
    for (; rowsPrinted < screenSize.first && row < state->getTotalLines(); ++row) {
        const std::string &line = state->getLine(row);
        int linesToTake = terminal->linesOccupied(line.length());
        if (rowsPrinted + linesToTake > screenSize.first) {
            didNotFit = true;
            break;
        }
        terminal->printString(FILEWINDOW, line);
        rowsPrinted += linesToTake;
        terminal->moveCursorInTerminal(FILEWINDOW, {rowsPrinted, 0});
    }
    if (didNotFit) {
        terminal->startColoredOutput(FILEWINDOW);
        for (; rowsPrinted <= screenSize.first; ++rowsPrinted) {
            terminal->printString(FILEWINDOW, "@");
            terminal->moveCursorInTerminal(FILEWINDOW, {rowsPrinted, 0});
        }
        terminal->stopColoredOutput(FILEWINDOW);
    }
    repositionCursor(state);
}

void VM::TerminalView::drawEmptyLines() {
    terminal->startColoredOutput(FILEWINDOW);
    terminal->moveCursorInTerminal(FILEWINDOW, std::pair<int, int>(1, 0));
    int currentRow = 1;
    int maxRowNumber = terminal->getWindowSize(FILEWINDOW).first;
    while (currentRow < maxRowNumber) {
        terminal->moveCursorInTerminal(FILEWINDOW, std::pair<int, int>(currentRow, 0));
        terminal->printString(FILEWINDOW, "~");
        ++currentRow;
    }
    terminal->stopColoredOutput(FILEWINDOW);
    terminal->moveCursorInTerminal(FILEWINDOW, std::pair<int, int>(0,0));
}

void VM::TerminalView::repositionCursor(WindowState *state) {
    int firstLine = state->getOffset();
    std::pair<int, int> screenSize = terminal->getWindowSize(FILEWINDOW);
    std::pair<int, int> cursorPosition = state->getCursor();
    int rowNumber = 0;
    if (cursorPosition.first != 0) {
        for(int i =firstLine; i < cursorPosition.first; ++i) {
            int length = state->getLine(i).length();
            rowNumber += terminal->linesOccupied(length);
        }
    }
    if (cursorPosition.second > screenSize.second) {
        cursorPosition.first = rowNumber + (cursorPosition.second/ screenSize.second);
    } else {
        cursorPosition.first = rowNumber;
    }
    cursorPosition.second = cursorPosition.second % screenSize.second;
    terminal->moveCursorInTerminal(FILEWINDOW, cursorPosition);
}
