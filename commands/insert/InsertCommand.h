#ifndef VM_INSERTCOMMAND_H
#define VM_INSERTCOMMAND_H

#include "../Command.h"

namespace VM {
    class InsertCommand: public Command {
    private:
        void executeFor(VMModel &model, int times) override = 0;

    public:
        InsertCommand() = default;
        ~InsertCommand() override = default;
    };
}

#endif //VM_INSERTCOMMAND_H
