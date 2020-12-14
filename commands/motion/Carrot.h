#ifndef VM_CARROT_H
#define VM_CARROT_H


#include "MotionCommand.h"

namespace VM {
    class Carrot: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        Carrot();
    };
}

#endif //VM_CARROT_H
