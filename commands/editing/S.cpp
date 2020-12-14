#include "S.h"
#include "../../model/VMModel.h"
#include "../insert/I.h"
#include "../cutpaste/X.h"

VM::S::S() {
    commandSequence.push_back('s');
}

void VM::S::executeFor(VM::VMModel &model, int times) {
    X x{false};
    x.execute(model, times);
    model.getActiveState()->revalidateCursorForLine();
    I i{false};
    i.execute(model, 1);
}
