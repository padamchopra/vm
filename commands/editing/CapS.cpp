#include "CapS.h"
#include "CC.h"

VM::CapS::CapS() {
    undoable = false;
    commandSequence.push_back('S');
}

void VM::CapS::executeFor(VM::VMModel &model, int times) {
    CC cc{};
    cc.execute(model, times);
}
