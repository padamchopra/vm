#ifndef VM_EXN_H
#define VM_EXN_H

#include "ExCommand.h"

namespace VM {
    class ExN: public ExCommand {
    private:
        void executeFor(VMModel &model, const std::string &inputSequence) override;

    public:
        ExN();
    };
}

#endif //VM_EXN_H
