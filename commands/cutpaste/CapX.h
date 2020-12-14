#ifndef VM_CAPX_H
#define VM_CAPX_H

#include "CutPasteCommand.h"

namespace VM {
    class CapX: public CutPasteCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        CapX();
    };
}

#endif //VM_CAPX_H
