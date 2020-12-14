#ifndef VM_EXWQ_H
#define VM_EXWQ_H

#include "ExCommand.h"

namespace VM {
    class ExWQ: public ExCommand {
    private:
        void executeFor(VMModel &model, const std::string &inputSequence) override;

    public:
        ExWQ();
    };
}

#endif //VM_EXWQ_H
