#include "B.h"
#include "../../model/VMModel.h"

VM::B::B() {
    commandSequence.push_back('b');
}

void VM::B::executeFor(VM::VMModel &model, int times) {
    while(times > 0) {
        executeOnce(model);
        --times;
    }
}

void VM::B::executeOnce(VMModel &model) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    if (cursor.second == 0 && cursor.first == 0){
        state->setCursor(std::pair<int, int>(0, 0));
    } else if (cursor.second == 0 && cursor.first > 0) {
        state->moveCursor(UP, model.getController());
        cursor = state->getCursor();
        int length = state->getLine(cursor.first).length();
        if (length != 0) {
            state->setCursor(std::pair<int, int>(cursor.first, length - 1));
            executeOnce(model);
        }
    } else {
        std::string line = state->getLine(cursor.first);
        bool found = false;
        for (size_t i= cursor.second - 1; i > 0; --i) {
            if (line.at(i) != ' ' && line.at(i-1) == ' ') {
                state->setCursor(std::pair<int, int>(cursor.first, i));
                found = true;
                break;
            }
        }
        if (!found) {
            state->setCursor(std::pair<int, int>(cursor.first, 0));
        }
    }
}
