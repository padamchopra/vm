#ifndef VM_I_H
#define VM_I_H

#include "InsertCommand.h"

namespace VM {
    class I: public InsertCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        I();
        I(bool canUndo);
    };
}

#endif //VM_I_H
