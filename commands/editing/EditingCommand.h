#ifndef VM_EDITINGCOMMAND_H
#define VM_EDITINGCOMMAND_H

#include "../Command.h"

namespace VM {
    class EditingCommand: public Command {
    private:
        void executeFor(VMModel &model, int times) override = 0;

    public:
        EditingCommand() = default;
        ~EditingCommand() override = default;
    };
}

#endif //VM_EDITINGCOMMAND_H
