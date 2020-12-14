#ifndef VM_DOT_H
#define VM_DOT_H

#include "EditingCommand.h"

namespace VM {
    class Dot: public EditingCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        Dot();
    };
}
#endif //VM_DOT_H
