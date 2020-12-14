#ifndef VM_QUESTION_H
#define VM_QUESTION_H

#include "MotionCommand.h"

namespace VM {
    class Question: public MotionCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        Question();
    };
}


#endif //VM_QUESTION_H
