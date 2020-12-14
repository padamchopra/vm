#ifndef VM_SLASH_H
#define VM_SLASH_H

#include "MotionCommand.h"

namespace VM {
    class Slash: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        Slash();
    };
}

#endif //VM_SLASH_H
