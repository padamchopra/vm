#ifndef VM_CONTROLU_H
#define VM_CONTROLU_H

#include "MotionCommand.h"

namespace VM {
    class ControlU: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;
        void executeOnce(VMModel &model);

    public:
        ControlU();
    };
}


#endif //VM_CONTROLU_H
