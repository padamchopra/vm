#ifndef VM_L_H
#define VM_L_H

#include "MotionCommand.h"

namespace VM {
    class L: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        L();
        int isAMatch(const std::vector<int> &inputSequence) override;
    };
}

#endif //VM_L_H
