#ifndef VM_CONTROLG_H
#define VM_CONTROLG_H

#include "MotionCommand.h"

namespace VM {
    class ControlG: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        ControlG();
    };
}

#endif //VM_CONTROLG_H
