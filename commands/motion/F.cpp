#include "F.h"
#include "../../model/VMModel.h"
#include "../../mode/NormalMode.h"

VM::F::F() {
    lookFor = '\0';
    commandSequence.push_back('f');
}

void VM::F::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    int newColumn = cursor.second + 1;
    std::string line = state->getLine(cursor.first);
    int length = line.length();
    char c;
    if (lookFor == '\0') {
        c = model.getInput().back();
        auto *mode = dynamic_cast<NormalMode*>(model.getMode(NORMAL_MODE));
        if (mode != nullptr) mode->setLastFInfo({true, c});
    } else {
        c = lookFor;
    }
    for (; newColumn < length && times > 0; ++newColumn) {
        if (line.at(newColumn) == c) {
            --times;
        }
    }
    if (times == 0) {
        state->setCursor(std::pair<int, int>(cursor.first, newColumn-1));
    }
}

VM::F::F(char look): F{} {
    lookFor = look;
}
