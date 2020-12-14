#ifndef VM_EXPREV_H
#define VM_EXPREV_H

#include "ExCommand.h"

namespace VM {
    class ExPrev: public ExCommand {
    private:
        void executeFor(VMModel &model, const std::string &inputSequence) override;

    public:
        ExPrev();
    };
}

#endif //VM_EXPREV_H
