#ifndef VM_B_H
#define VM_B_H

#include "./MotionCommand.h"

namespace VM {
    class B: public MotionCommand {
    private:
        void executeOnce(VMModel &model);
        void executeFor(VMModel &model, int times) override;

    public:
        B();
    };
}


#endif //VM_B_H
