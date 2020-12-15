#ifndef VM_EXE_H
#define VM_EXE_H


#include "ExCommand.h"

namespace VM {
    class ExE: public ExCommand {
    private:
        void executeFor(VMModel &model, const std::string &inputSequence) override;

    public:
        ExE();
    };
}

#endif //VM_EXE_H
