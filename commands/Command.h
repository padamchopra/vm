#ifndef VM_COMMAND_H
#define VM_COMMAND_H

#include <vector>
#include <string>
#include "../state/WindowState.h"

enum InteractionType {ALL = 0, LINE = 1};
namespace VM {
    class VMModel;
    class Command {
    private:
        virtual void executeFor(VMModel &model, int times) = 0;

    protected:
        bool undoable;
        bool countable;
        bool recordable;
        std::vector<int> commandSequence;

    public:
        Command();
        virtual ~Command() = default;
        virtual int isAMatch(const std::vector<int> &inputSequence);
        virtual void execute(VMModel &model, int times);
        bool isUndoable() const;
        bool isRecordable() const;
    };
}

#endif //VM_COMMAND_H
