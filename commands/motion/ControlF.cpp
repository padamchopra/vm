#include "ControlF.h"
#include "../../model/VMModel.h"
#include "../../controller/TerminalController.h"

VM::ControlF::ControlF() {
    commandSequence.push_back(CTRL_F);
}

void VM::ControlF::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    state->setCursor({state->getCursor().first, 0});
    while (times > 0) {
        executeOnce(model);
        --times;
    }
}

void VM::ControlF::executeOnce(VM::VMModel &model) {
    WindowState *state = model.getActiveState();
        TerminalController *controller = model.getController();
        int remainingScreenHeight = controller->outputWindowHeight();
        int offset = state->getOffset();
        int lastPrintedLine = -1;
        remainingScreenHeight = remainingScreenHeight - controller->linesAsOutput(state->getLine(offset).length());
        int totallines = state->getTotalLines();
        while (remainingScreenHeight >= 0 && offset < totallines - 1) {
            ++offset;
            lastPrintedLine = offset;
            int linesNeeded = controller->linesAsOutput(state->getLine(offset).length());
            if (linesNeeded > remainingScreenHeight) {
                break;
            } else {
                remainingScreenHeight -= linesNeeded;
            }
        }
        --lastPrintedLine;
        if (lastPrintedLine >= totallines) lastPrintedLine = totallines - 1;
        if (lastPrintedLine < 0) lastPrintedLine = 0;
        state->setOffset(lastPrintedLine);
        state->setCursor({lastPrintedLine, 0});
}
