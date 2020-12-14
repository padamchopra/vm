#ifndef VM_CAPJ_H
#define VM_CAPJ_H

#include "EditingCommand.h"

namespace VM {
    class CapJ: public EditingCommand {
    private:
        void executeFor(VMModel &model, int times) override;
        void executeOnce (VMModel &model);

    public:
        CapJ();
    };
}

#endif //VM_CAPJ_H
