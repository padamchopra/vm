#include "I.h"
#include "../../model/VMModel.h"
#include "../../mode/InsertMode.h"

VM::I::I() {
    commandSequence.push_back('i');
}

void VM::I::executeFor(VM::VMModel &model, int times) {
    auto *im = dynamic_cast<InsertMode*>(model.getMode(INSERT_MODE));
    if (im != nullptr){
        im->setCountForCall(times);
    }
    model.changeMode(INSERT_MODE);
    std::string message = "-- INSERT MODE --";
    model.updateStatus(message);
}

VM::I::I(bool canUndo): I{} {
    undoable = canUndo;
}
