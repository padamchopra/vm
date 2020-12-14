#ifndef VM_EXQEXCLAMATION_H
#define VM_EXQEXCLAMATION_H

#include "ExCommand.h"

namespace VM {
    class ExQExclamation: public ExCommand {
    private:
        void executeFor(VMModel &model, const std::string &inputSequence) override;

    public:
        ExQExclamation();
    };
}

#endif //VM_EXQEXCLAMATION_H
