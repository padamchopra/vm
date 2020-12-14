#ifndef VM_K_H
#define VM_K_H

#include "MotionCommand.h"

namespace VM {
    class K: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        K();
        int isAMatch(const std::vector<int> &inputSequence) override;
    };
}


#endif //VM_K_H
