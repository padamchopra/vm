#ifndef VM_O_H
#define VM_O_H

#include "InsertCommand.h"

namespace VM {
    class O: public InsertCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        O();
    };
}


#endif //VM_O_H
