#ifndef VM_CAPN_H
#define VM_CAPN_H

#include "MotionCommand.h"

namespace VM {
    class CapN: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        CapN();
        void execute(VMModel &model, int times) override;
    };
}

#endif //VM_CAPN_H
