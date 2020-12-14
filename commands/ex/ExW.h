#ifndef VM_EXW_H
#define VM_EXW_H

#include "ExCommand.h"

namespace VM {
    class ExW: public ExCommand {
    private:
        void executeFor(VMModel &model, const std::string &inputSequence) override;

    public:
        ExW();
    };
}

#endif //VM_EXW_H
