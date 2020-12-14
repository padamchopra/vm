#ifndef VM_H_H
#define VM_H_H

#include "MotionCommand.h"

namespace VM{
    class H: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        H();
        int isAMatch(const std::vector<int> &inputSequence) override;
    };
}


#endif //VM_H_H
