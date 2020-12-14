#ifndef VM_EXDOLLAR_H
#define VM_EXDOLLAR_H

#include "ExCommand.h"

namespace VM {
    class ExDollar: public ExCommand {
    private:
        void executeFor(VMModel &model, const std::string &inputSequence) override;

    public:
        ExDollar();
    };
}

#endif //VM_EXDOLLAR_H
