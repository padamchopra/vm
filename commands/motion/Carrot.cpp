#include "Carrot.h"
#include "../../model/VMModel.h"

VM::Carrot::Carrot() {
    countable = false;
    commandSequence.push_back('^');
}

void VM::Carrot::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    std::string line = state->getLine(cursor.first);
    for (size_t i = 0; i < line.length(); ++i) {
        if (line.at(i) != ' ') {
            cursor.second = i;
            break;
        }
    }
    state->setCursor({cursor.first, cursor.second});
}
