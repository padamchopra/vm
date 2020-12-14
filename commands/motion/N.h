#ifndef VM_N_H
#define VM_N_H

#include "MotionCommand.h"

namespace VM {
    class N: public MotionCommand {
    private:
        bool flip;
        int direction;
        std::string searchFor;
        std::string statusBarOutput;
        bool errorOccured;
        void executeFor(VMModel &model, int times) override;
        bool doesPhraseEvenExist(WindowState *state);
        void executeOnce(VMModel &model, int colOffset);

    public:
        N();
        N(bool flipDirection);
        void execute(VMModel &model, int times) override;
    };
}

#endif //VM_N_H
