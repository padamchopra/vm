#ifndef VM_CAPS_H
#define VM_CAPS_H

#include "EditingCommand.h"

namespace VM {
    class CapS: public EditingCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        CapS();
    };
}

#endif //VM_CAPS_H
