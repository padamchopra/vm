#ifndef VM_CAPP_H
#define VM_CAPP_H


#include "CutPasteCommand.h"

namespace VM {
    class CapP: public CutPasteCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        CapP();
    };
}

#endif //VM_CAPP_H
