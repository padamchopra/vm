#include "J.h"
#include "../../model/VMModel.h"

VM::J::J() {
    commandSequence.push_back('j');
}

void VM::J::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    while (times > 0) {
        state->moveCursor(DOWN, model.getController());
        --times;
    }
}

int VM::J::isAMatch(const std::vector<int> &inputSequence) {
    int result = Command::isAMatch(inputSequence);
    if (result == 0) {
        commandSequence.clear();
        commandSequence.push_back(DARROW);
        result = Command::isAMatch(inputSequence);
        commandSequence.clear();
        commandSequence.push_back('j');
        return result;
    } else {
        return result;
    }
}

