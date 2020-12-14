#ifndef VM_EXAUTH_H
#define VM_EXAUTH_H


#include "ExCommand.h"

namespace VM {
    class ExAuth: public ExCommand {
    private:
        void executeFor(VMModel &model, const std::string &inputSequence) override;

    public:
        ExAuth();
    };
}

#endif //VM_EXAUTH_H
