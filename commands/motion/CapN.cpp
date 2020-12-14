#include "CapN.h"
#include "../../model/VMModel.h"
#include "N.h"

VM::CapN::CapN() {
    commandSequence.push_back('N');
}

void VM::CapN::executeFor(VM::VMModel &model, int times) {}

void VM::CapN::execute(VM::VMModel &model, int times) {
    N n{true};
    n.execute(model, times);
}
