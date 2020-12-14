#ifndef VM_A_H
#define VM_A_H

#include "./InsertCommand.h"

namespace VM {
    class A: public InsertCommand {
    private:
        void executeFor(VMModel &model, int times) override;

    public:
        A();
        A(bool canUndo);
    };
}

#endif //VM_A_H
