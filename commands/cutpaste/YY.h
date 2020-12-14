#ifndef VM_YY_H
#define VM_YY_H

#include "CutPasteCommand.h"

namespace VM {
    class YY: public CutPasteCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        YY();
    };
}


#endif //VM_YY_H
