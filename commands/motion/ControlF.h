#ifndef VM_CONTROLF_H
#define VM_CONTROLF_H

#include "MotionCommand.h"

namespace VM {
    class ControlF: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;
        void executeOnce(VMModel &model);

    public:
        ControlF();
    };
}


#endif //VM_CONTROLF_H
