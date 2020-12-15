#include "Command.h"
#include "../model/VMModel.h"
#include "../mode/NormalMode.h"
#include <algorithm>

VM::Command::Command() : undoable(true), countable(true), recordable(true) {}

void VM::Command::execute(VM::VMModel &model, int times) {
    if (undoable && !model.isPlaying()) {
        model.getActiveState()->memoriseState(model.getController());
    }
    if (!countable) {
        times = 1;
    }
    executeFor(model, times);
    model.updateView(model.getActiveState());
    model.clearInputSequence();
}

int VM::Command::isAMatch(const std::vector<int> &inputSequence) {
    if (commandSequence.size() > inputSequence.size()) return 0;
    auto inputIterator = inputSequence.rbegin();
    bool match = true;
    for (auto it = commandSequence.rbegin(); it != commandSequence.rend() && inputIterator != inputSequence.rend(); ++it) {
        if (*it != *inputIterator) {
            match = false;
            break;
        }
        ++inputIterator;
    }
    if (match) {
        std::string count;
        for(; inputIterator != inputSequence.rend(); ++inputIterator) {
            char c = static_cast<char>(*inputIterator);
            if (isdigit(c)) count += c;
            else break;
        }
        if (count.empty()) return 1;
        else {
            std::reverse(count.begin(), count.end());
            return std::stoi(count);
        }
    } else return 0;
}

bool VM::Command::isRecordable() const {
    return recordable;
}

bool VM::Command::isUndoable() const {
    return undoable;
}
