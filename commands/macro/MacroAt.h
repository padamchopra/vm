#ifndef VM_MACROAT_H
#define VM_MACROAT_H

#include "MacroCommand.h"

namespace VM {
    class MacroAt: public MacroCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        MacroAt();
    };
}

#endif //VM_MACROAT_H
