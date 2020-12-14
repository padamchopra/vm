#include "R.h"
#include "../../model/VMModel.h"

VM::R::R() {
    commandSequence.push_back('r');
}

void VM::R::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    std::string line = state->getLine(cursor.first);
    char c = model.getInput().back();
    if (cursor.second + times <= (int) line.length()) {
        std::string newLine = line.substr(0, cursor.second);
        int i = cursor.second;
        for (; i < cursor.second + times; ++i) {
            newLine += c;
        }
        newLine += line.substr(i);
        state->setLine(cursor.first, newLine);
        state->setCursor({cursor.first, cursor.second + times - 1});
    }
}
