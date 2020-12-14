#ifndef VM_W_H
#define VM_W_H

#include "MotionCommand.h"

namespace VM {
    class W: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;
        bool executeOnce(VMModel &model);

    public:
        W();
    };
}

#endif //VM_W_H
