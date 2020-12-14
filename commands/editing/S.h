#ifndef VM_S_H
#define VM_S_H


#include "EditingCommand.h"

namespace VM {
    class S: public EditingCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        S();
    };
}

#endif //VM_S_H
