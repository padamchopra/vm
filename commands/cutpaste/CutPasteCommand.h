#ifndef VM_CUTPASTECOMMAND_H
#define VM_CUTPASTECOMMAND_H

#include "../Command.h"

namespace VM {
    class CutPasteCommand: public Command {
    private:
        void executeFor(VMModel &model, int times) override = 0;

    public:
        CutPasteCommand() = default;
        ~CutPasteCommand() override = default;
    };
}

#endif //VM_CUTPASTECOMMAND_H
