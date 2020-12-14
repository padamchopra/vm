#include "CC.h"
#include "../../model/VMModel.h"
#include "../insert/I.h"
#include "../cutpaste/DD.h"

VM::CC::CC() {
    commandSequence.push_back('c');
    commandSequence.push_back('c');
}

void VM::CC::executeFor(VM::VMModel &model, int times) {
    DD dd{false};
    dd.execute(model, times);
    WindowState *state = model.getActiveState();
    if (state->getTotalLines() != 1 && !state->getLine(0).empty()) {
        state->addLine(state->getCursor().first, "");
        state->revalidateCursorForLine();
    }
    I i{false};
    i.execute(model, 1);
}
