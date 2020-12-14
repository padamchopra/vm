#ifndef VM_CONTROLD_H
#define VM_CONTROLD_H

#include "MotionCommand.h"

namespace VM {
    class ControlD: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;
        void executeOnce(VMModel &model);

    public:
        ControlD();
    };
}

#endif //VM_CONTROLD_H
