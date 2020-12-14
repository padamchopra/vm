#include "H.h"
#include "../../model/VMModel.h"

VM::H::H() {
    commandSequence.push_back('h');
}

void VM::H::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    while (times > 0) {
        state->moveCursor(LEFT, model.getController());
        --times;
    }
}

int VM::H::isAMatch(const std::vector<int> &inputSequence) {
    int result = Command::isAMatch(inputSequence);
    if (result == 0) {
        commandSequence.clear();
        commandSequence.push_back(LARROW);
        result = Command::isAMatch(inputSequence);
        commandSequence.clear();
        commandSequence.push_back('h');
        return result;
    } else {
        return result;
    }
}

