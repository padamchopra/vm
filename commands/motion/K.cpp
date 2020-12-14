#include "K.h"
#include "../../model/VMModel.h"

VM::K::K() {
    commandSequence.push_back('k');
}

void VM::K::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    while (times > 0) {
        state->moveCursor(UP, model.getController());
        --times;
    }
}

int VM::K::isAMatch(const std::vector<int> &inputSequence) {
    int result = Command::isAMatch(inputSequence);
    if (result == 0) {
        commandSequence.clear();
        commandSequence.push_back(UARROW);
        result = Command::isAMatch(inputSequence);
        commandSequence.clear();
        commandSequence.push_back('k');
        return result;
    } else {
        return result;
    }
}
