#ifndef VM_U_H
#define VM_U_H

#include "EditingCommand.h"

namespace VM {
    class U: public EditingCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        U();
    };
}

#endif //VM_U_H
