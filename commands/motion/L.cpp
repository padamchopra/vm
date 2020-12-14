#include "L.h"
#include "../../model/VMModel.h"

VM::L::L() {
    commandSequence.push_back('l');
}

void VM::L::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    while (times > 0) {
        state->moveCursor(RIGHT, model.getController());
        --times;
    }
}

int VM::L::isAMatch(const std::vector<int> &inputSequence) {
    int result = Command::isAMatch(inputSequence);
    if (result == 0) {
        commandSequence.clear();
        commandSequence.push_back(RARROW);
        result = Command::isAMatch(inputSequence);
        commandSequence.clear();
        commandSequence.push_back('l');
        return result;
    } else {
        return result;
    }
}
