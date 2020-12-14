#ifndef VM_EXQ_H
#define VM_EXQ_H

#include "ExCommand.h"

namespace VM {
    class ExQ: public ExCommand {
    private:
        void executeFor(VMModel &model, const std::string &inputSequence) override;

    public:
        ExQ();
    };
}

#endif //VM_EXQ_H
