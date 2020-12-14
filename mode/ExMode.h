#ifndef VM_EXMODE_H
#define VM_EXMODE_H

#include "Mode.h"
#include "../commands/ex/ExCommand.h"

namespace VM {
    class ExMode: public Mode {
    private:
        std::vector<std::unique_ptr<ExCommand>> commands;
        void parseInputSequence(const std::vector<int> &inputSequence) override;
        void prepareForExit();
        void constructCommands();

    public:
        ExMode(VMModel &model);
    };
}

#endif //VM_EXMODE_H
