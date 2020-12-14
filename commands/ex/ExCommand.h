#ifndef VM_EXCOMMAND_H
#define VM_EXCOMMAND_H

#include "../Command.h"

namespace VM {
    class VMModel;
    class ExCommand {
    private:
        virtual void executeFor(VMModel &model, const std::string &inputSequence) = 0;

    protected:
        std::vector<int> commandSequence;

    public:
        ExCommand() = default;
        virtual bool isAMatch(const std::vector<int> &inputSequence);
        virtual void execute(VMModel &model, const std::vector<int> &inputSequence);
        virtual ~ExCommand() = default;
    };
}

#endif //VM_EXCOMMAND_H
