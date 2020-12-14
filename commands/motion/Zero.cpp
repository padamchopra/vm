#include "Zero.h"
#include "../../model/VMModel.h"

void VM::Zero::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    state->setCursor({state->getCursor().first, 0});
}

VM::Zero::Zero() {
    countable = false;
    commandSequence.push_back('0');
}

int VM::Zero::isAMatch(const std::vector<int> &inputSequence) {
    if (inputSequence.size() > 1 && isdigit(static_cast<char>(inputSequence.at(inputSequence.size() - 1)))) {
        return 0;
    }
    return Command::isAMatch(inputSequence);
}
