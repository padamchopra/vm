#include "DD.h"
#include "../../model/VMModel.h"
#include "../../mode/NormalMode.h"

VM::DD::DD() {
    commandSequence.push_back('d');
    commandSequence.push_back('d');
}

VM::DD::DD(bool canUndo): DD{} {
    undoable = canUndo;
}

void VM::DD::executeFor(VM::VMModel &model, int times) {
    WindowState *state = model.getActiveState();
    std::pair<int, int> cursor = state->getCursor();
    if (times > 1 && cursor.first == state->getTotalLines() - 1) {
        return; // observed
    }
    auto *mode = dynamic_cast<NormalMode*>(model.getMode(NORMAL_MODE));
    std::vector<std::string> clip;
    while (times > 0 && cursor.first < state->getTotalLines()) {
        clip.emplace_back(state->getLine(cursor.first));
        state->removeLine(cursor.first);
        --times;
    }

    if (mode != nullptr) {
        mode->setClipBoard({LINE, clip});
    }

    if (cursor.first >= state->getTotalLines()) {
        state->moveCursor(UP, model.getController());
        state->setCursor(std::pair<int, int>(state->getCursor().first, 0));
    }
    if (state->getTotalLines() == 0) {
        state->addLine(0, "");
        std::string message = "\"" + state->getFileName() + "\"" + " -- FILE BUFFER EMPTY --";
        model.updateStatus(message);
    }
    state->revalidateCursorForLine();
}
