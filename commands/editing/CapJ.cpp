#include "CapJ.h"
#include "../../model/VMModel.h"

VM::CapJ::CapJ() {
    commandSequence.push_back('J');
}

void VM::CapJ::executeFor(VM::VMModel &model, int times) {
    times = times == 1 ? 1 : times - 1;
    while (times > 0) {
        executeOnce(model);
        --times;
    }
}

void VM::CapJ::executeOnce(VM::VMModel &model) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    if (cursor.first + 1 < state->getTotalLines()) {
        std::string newLine = state->getLine(cursor.first) + " ";
        int newColumn = newLine.length() - 1;
        newLine += state->getLine(cursor.first + 1);
        state->removeLine(cursor.first + 1);
        state->setCursor({cursor.first, newColumn});
        state->setLine(cursor.first, newLine);
    }

}
