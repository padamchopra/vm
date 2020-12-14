#ifndef VM_SEMICOLON_H
#define VM_SEMICOLON_H

#include "MotionCommand.h"

namespace VM {
    class SemiColon: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        SemiColon();
    };
}

#endif //VM_SEMICOLON_H
