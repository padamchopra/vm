#ifndef VM_CONTROLR_H
#define VM_CONTROLR_H

#include "EditingCommand.h"

namespace VM {
    class ControlR: public EditingCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        ControlR();
    };
}

#endif //VM_CONTROLR_H
