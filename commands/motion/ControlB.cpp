#include "ControlB.h"
#include "../../model/VMModel.h"
#include "../../controller/TerminalController.h"

VM::ControlB::ControlB() {
    commandSequence.push_back(CTRL_B);
}

void VM::ControlB::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    state->setCursor({state->getCursor().first, 0});
    while (times > 0) {
        executeOnce(model);
        --times;
    }
}

void VM::ControlB::executeOnce(VM::VMModel &model) {
    WindowState *state = model.getActiveState();
    if (state->getOffset() == 0) {
        state->setCursor({0, 0});
    } else {
        TerminalController *controller = model.getController();
        int remainingScreenHeight = controller->outputWindowHeight();
        int offset = state->getOffset();
        remainingScreenHeight = remainingScreenHeight - controller->linesAsOutput(state->getLine(offset).length());
        while (remainingScreenHeight > 0 && offset > 0) {
            --offset;
            int linesNeeded = controller->linesAsOutput(state->getLine(offset).length());
            if (linesNeeded > remainingScreenHeight) {
                ++offset;
                break;
            } else {
                remainingScreenHeight -= linesNeeded;
            }
        }
        state->setOffset(offset);
        state->setCursor({offset, 0});
    }
}
