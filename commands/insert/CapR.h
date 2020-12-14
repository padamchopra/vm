#ifndef VM_CAPR_H
#define VM_CAPR_H

#include "InsertCommand.h"

namespace VM {
    class CapR: public InsertCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        CapR();
    };
}

#endif //VM_CAPR_H
