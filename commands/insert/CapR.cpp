#include "CapR.h"
#include "../../model/VMModel.h"
#include "../../mode/InsertMode.h"

VM::CapR::CapR() {
    commandSequence.push_back('R');
}

void VM::CapR::executeFor(VM::VMModel &model, int times) {
    auto *im = dynamic_cast<InsertMode*>(model.getMode(INSERT_MODE));
    if (im != nullptr){
        im->setCountForCall(times);
        im->setReplaceMode(true);
    }
    model.changeMode(INSERT_MODE);
    std::string message = "-- REPLACE --";
    model.updateStatus(message);
}
