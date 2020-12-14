#ifndef VM_EXZERO_H
#define VM_EXZERO_H

#include "ExCommand.h"

namespace VM {
    class ExZero: public ExCommand {
    private:
        void executeFor(VMModel &model, const std::string &inputSequence) override;

    public:
        ExZero();
    };
}

#endif //VM_EXZERO_H
