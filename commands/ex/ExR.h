#ifndef VM_EXR_H
#define VM_EXR_H

#include "ExCommand.h"

namespace VM {
    class ExR: public ExCommand {
    private:
        void executeFor(VMModel &model, const std::string &inputSequence) override;

    public:
        ExR();
    };
}

#endif //VM_EXR_H
