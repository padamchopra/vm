#ifndef VM_MACROCOMMAND_H
#define VM_MACROCOMMAND_H

#include "../Command.h"

namespace VM {
    class MacroCommand: public Command {
    private:
        void executeFor(VMModel &model, int times) override = 0;

    public:
        MacroCommand() {
            undoable = false;
            dottable = false;
        };
        ~MacroCommand() override = default;
    };
}

#endif //VM_MACROCOMMAND_H
