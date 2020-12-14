#include "X.h"
#include "../../model/VMModel.h"
#include "../../mode/NormalMode.h"

VM::X::X() {
    commandSequence.push_back('x');
}

void VM::X::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    std::string line = state->getLine(cursor.first);
    std::string copied = line.substr(cursor.second, times);
    line = line.erase(cursor.second, times);
    state->setLine(cursor.first, line);
    state->revalidateCursorForLine();
    auto *mode = dynamic_cast<NormalMode*>(model.getMode(NORMAL_MODE));
    if (mode != nullptr) {
        std::vector<std::string> clip;
        clip.emplace_back(copied);
        mode->setClipBoard({ALL, clip});
    }
}

VM::X::X(bool canUndo): X{} {
    undoable = canUndo;
}
