#include "ExAuth.h"
#include "../../model/VMModel.h"

void VM::ExAuth::executeFor(VM::VMModel &model, const std::string &inputSequence) {
    model.updateStatus("VM. Created by Padam Chopra (web: padamchopra.me)");
}

VM::ExAuth::ExAuth() {
    commandSequence.push_back('a');
    commandSequence.push_back('u');
    commandSequence.push_back('t');
    commandSequence.push_back('h');
}
