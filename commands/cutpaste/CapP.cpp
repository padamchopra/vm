#include "CapP.h"
#include "P.h"

VM::CapP::CapP() {
    commandSequence.push_back('P');
}

void VM::CapP::executeFor(VM::VMModel &model, int times) {
    P p{false, true};
    p.execute(model, times);
}


