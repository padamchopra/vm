#ifndef VM_CAPA_H
#define VM_CAPA_H

#include "InsertCommand.h"

namespace VM {
    class CapA: public InsertCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        CapA();
    };
}

#endif //VM_CAPA_H
