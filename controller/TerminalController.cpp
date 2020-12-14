#include "TerminalController.h"
#include "../utility/Terminal.h"

VM::TerminalController::TerminalController(const std::shared_ptr<Terminal> &terminal) : Controller(terminal) {}

int VM::TerminalController::getKeyPress() const {
    return terminal->getKeyStroke(FILEWINDOW);
}

int VM::TerminalController::linesAsOutput(int length) const {
    return terminal->linesOccupied(length);
}

int VM::TerminalController::outputWindowHeight() const {
    return terminal->getWindowSize(FILEWINDOW).first;
}

void VM::TerminalController::doClearStatus() const {
    terminal->clear(STATUSBAR);
}

void VM::TerminalController::positionCursorAtStatus(int x) {
    terminal->moveCursorInTerminal(STATUSBAR, {0, x});
}
