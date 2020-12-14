#ifndef VM_SWITCHEX_H
#define VM_SWITCHEX_H

#include "EditingCommand.h"

namespace VM {
    class SwitchEx: public EditingCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        SwitchEx();
        void execute(VMModel &model, int times) override;
    };
}

#endif //VM_SWITCHEX_H
