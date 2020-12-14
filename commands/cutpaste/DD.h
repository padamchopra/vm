#ifndef VM_DD_H
#define VM_DD_H

#include "CutPasteCommand.h"

namespace VM {
    class DD: public CutPasteCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        DD();
        DD(bool canUndo);
    };
}

#endif //VM_DD_H
