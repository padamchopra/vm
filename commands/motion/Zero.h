#ifndef VM_ZERO_H
#define VM_ZERO_H

#include "MotionCommand.h"

namespace VM {
    class Zero: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        Zero();
        int isAMatch(const std::vector<int> &inputSequence) override;
    };
}

#endif //VM_ZERO_H
