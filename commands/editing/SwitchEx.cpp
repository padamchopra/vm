#include "SwitchEx.h"
#include "../../model/VMModel.h"
#include "../../controller/TerminalController.h"

void VM::SwitchEx::executeFor(VM::VMModel &model, int times) {
    model.changeMode(EX_MODE);
}

VM::SwitchEx::SwitchEx() {
    undoable = false;
    countable = false;
    commandSequence.push_back(':');
}

void VM::SwitchEx::execute(VM::VMModel &model, int times) {
    Command::execute(model, times);
    model.updateStatus(":");
    model.getController()->positionCursorAtStatus(1);
}
