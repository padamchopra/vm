#ifndef VM_EXLINENUMBER_H
#define VM_EXLINENUMBER_H

#include "ExCommand.h"

namespace VM {
    class ExLineNumber: public ExCommand {
    private:
        void executeFor(VMModel &model, const std::string &inputSequence) override;

    public:
        ExLineNumber();

        bool isAMatch(const std::vector<int> &inputSequence) override;
    };
}

#endif //VM_EXLINENUMBER_H
