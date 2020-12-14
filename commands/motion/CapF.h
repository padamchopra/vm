#ifndef VM_CAPF_H
#define VM_CAPF_H


#include "MotionCommand.h"

namespace VM {
    class CapF: public MotionCommand {
    private:
        char lookFor;
        void executeFor(VMModel &model, int times) override;

    public:
        CapF();
        CapF(char look);
    };
}


#endif //VM_CAPF_H
