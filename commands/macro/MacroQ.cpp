#include "MacroQ.h"
#include "../../model/VMModel.h"

void VM::MacroQ::executeFor(VM::VMModel &model, int times) {
    if (model.isRecording()) {
        model.stopRecordingSequence();
        model.updateStatus("saved macro");
    } else {
        std::string name;
        int c = model.getInput().back();
        if (model.isEnhanced()) {
            while (c != ENTER) {
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
                model.updateStatus("macro: " + name + " (press enter to start, esc to cancel)");
                c = model.getInput().back();
            }
            model.startRecordingSequence(name);
            model.updateStatus("");
        } else {
            if (isalnum(c)) {
                name = (char) c;
                model.startRecordingSequence(name);
                model.updateStatus("");
            } else {
                model.updateStatusWithError("not a valid name for a macro");
            }
        }
    }
}

VM::MacroQ::MacroQ() {
    countable = false;
    recordable = false;
    commandSequence.push_back('q');
}
