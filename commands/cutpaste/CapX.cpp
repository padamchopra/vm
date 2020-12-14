#include "CapX.h"
#include "../../model/VMModel.h"
#include "../../mode/NormalMode.h"

VM::CapX::CapX() {
    commandSequence.push_back('X');
}

void VM::CapX::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    std::string line = state->getLine(cursor.first);
    int newCursor = cursor.second - times;
    if (newCursor < 0) newCursor = 0;
    cursor.second = cursor.second - newCursor;
    std::string copied = line.substr(newCursor, cursor.second);
    line = line.erase(newCursor, cursor.second);
    state->setLine(cursor.first, line);
    state->setCursor({cursor.first, newCursor});
    state->revalidateCursorForLine();
    auto *mode = dynamic_cast<NormalMode*>(model.getMode(NORMAL_MODE));
    if (mode != nullptr) {
        std::vector<std::string> clip;
        clip.emplace_back(copied);
        mode->setClipBoard({ALL, clip});
    }
}
