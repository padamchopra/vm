#ifndef VM_R_H
#define VM_R_H

#include "EditingCommand.h"

namespace VM {
    class R: public EditingCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        R();
    };
}

#endif //VM_R_H
