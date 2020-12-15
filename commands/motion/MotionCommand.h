#ifndef VM_MOTIONCOMMAND_H
#define VM_MOTIONCOMMAND_H

#include "../Command.h"

enum FindInDirection {FORWARD = 1, BACKWARD = 0};
namespace VM {
    class MotionCommand: public Command {
    private:
        void executeFor(VMModel &model, int times) override = 0;

    public:
        MotionCommand() {
            undoable = false;
        };
        ~MotionCommand() override = default;
    };
}

#endif //VM_MOTIONCOMMAND_H
