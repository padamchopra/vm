#ifndef VM_DOLLAR_H
#define VM_DOLLAR_H


#include "MotionCommand.h"

namespace VM {
    class Dollar: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        Dollar();
    };
}

#endif //VM_DOLLAR_H
