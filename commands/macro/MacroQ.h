#ifndef VM_MACROQ_H
#define VM_MACROQ_H


#include "MacroCommand.h"

namespace VM {
    class MacroQ: public MacroCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        MacroQ();
    };
}

#endif //VM_MACROQ_H
