#ifndef VM_CAPO_H
#define VM_CAPO_H


#include "InsertCommand.h"

namespace VM {
    class CapO: public InsertCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        CapO();
    };
}

#endif //VM_CAPO_H
