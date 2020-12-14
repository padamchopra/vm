#include "YY.h"
#include "../../model/VMModel.h"
#include "../../mode/NormalMode.h"

VM::YY::YY() {
    undoable = false;
    commandSequence.push_back('y');
    commandSequence.push_back('y');
}

void VM::YY::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    std::vector<std::string> clip;
    std::string message = std::to_string(times);
    message = message + (times == 1 ? " line yanked" : " lines yanked");
    while (times > 0 && cursor.first < state->getTotalLines()) {
        clip.emplace_back(state->getLine(cursor.first));
        --times;
        ++cursor.first;
    }

    auto *mode = dynamic_cast<NormalMode*>(model.getMode(NORMAL_MODE));
    if (mode != nullptr) {
        mode->setClipBoard({LINE, clip});
    }
    model.updateStatus(message);
}
