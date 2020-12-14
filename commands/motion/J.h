#ifndef VM_J_H
#define VM_J_H

#include "MotionCommand.h"

namespace VM {
    class J: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        J();
        int isAMatch(const std::vector<int> &inputSequence) override;
    };
}


#endif //VM_J_H
