#ifndef VM_X_H
#define VM_X_H

#include "CutPasteCommand.h"

namespace VM {
    class X: public CutPasteCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        X();
        X(bool canUndo);
    };
}


#endif //VM_X_H
