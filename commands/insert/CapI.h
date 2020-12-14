#ifndef VM_CAPI_H
#define VM_CAPI_H

#include "InsertCommand.h"

namespace VM {
    class CapI: public InsertCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        CapI();
    };
}

#endif //VM_CAPI_H
