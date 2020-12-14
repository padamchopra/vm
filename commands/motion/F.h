#ifndef VM_F_H
#define VM_F_H

#include "MotionCommand.h"

namespace VM {
    class F: public MotionCommand {
    private:
        char lookFor;
        void executeFor(VMModel &model, int times) override;

    public:
        F();
        F(char look);
    };
}

#endif //VM_F_H
