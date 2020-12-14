#ifndef VM_CONTROLB_H
#define VM_CONTROLB_H

#include "MotionCommand.h"

namespace VM {
    class ControlB: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;
        void executeOnce(VMModel &model);

    public:
        ControlB();
    };
}

#endif //VM_CONTROLB_H
