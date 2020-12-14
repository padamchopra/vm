#include "MacroAt.h"
#include "../../model/VMModel.h"

void VM::MacroAt::executeFor(VM::VMModel &model, int times) {
    std::string name;
    int c = model.getInput().back();
    while (c != ENTER) {
        if (c == '@') {
            model.updateStatus("");
            model.playMacro(model.getLastPlayedMacro());
            return;
        }
        if (isalnum(c)) {
            name += (char) c;
        } else if (c == BACKSPACE) {
            if (name.size() == 1) {
                model.updateStatus("");
                return;
            } else {
                name = name.substr(0, name.size() - 1);
            }
        } else if (c == ESC) {
            model.updateStatus("");
            return;
        }
        model.updateStatus("macro: " + name + " (press enter to run, esc to cancel)");
        c = model.getInput().back();
    }
    model.updateStatus("");
    model.playMacro(name);
}

VM::MacroAt::MacroAt() {
    commandSequence.push_back('@');
}