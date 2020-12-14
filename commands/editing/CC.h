#ifndef VM_CC_H
#define VM_CC_H

#include "EditingCommand.h"

namespace VM {
    class CC: public EditingCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        CC();
    };
}


#endif //VM_CC_H
