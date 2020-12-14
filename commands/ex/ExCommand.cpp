#include "ExCommand.h"
#include "../../model/VMModel.h"

void VM::ExCommand::execute(VMModel &model, const std::vector<int> &inputSequence) {
    std::string sequence;
    for (int c: inputSequence) {
        if (c != LARROW && c!= RARROW && c != DARROW && c != UARROW) {
            sequence += (char) c;
        }
    }
    executeFor(model, sequence);
    model.clearInputSequence();
}

bool VM::ExCommand::isAMatch(const std::vector<int> &inputSequence) {
    if (commandSequence.size() > inputSequence.size() - 1) {
        return false;
    } else {
        size_t i = 0;
        for (; i < commandSequence.size(); ++i) {
            if (commandSequence.at(i) != inputSequence.at(i)) {
                return false;
            }
        }
        if (commandSequence.size() == inputSequence.size() -1 || ((char) inputSequence.at(i)) == ' ') {
            return true;
        } else {
            return false;
        }
    }
}