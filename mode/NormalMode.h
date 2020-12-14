#ifndef VM_NORMALMODE_H
#define VM_NORMALMODE_H

#include "Mode.h"
#include "../commands/Command.h"
#include <vector>
#include <memory>

namespace VM {
    class NormalMode: public Mode {
    private:
        std::pair<bool, char> lastFInfo;
        std::vector<std::unique_ptr<Command>> commands;
        std::vector<std::string> clipBoard;
        std::vector<int> lastInputSequenceBeforeCommandRun;
        Command *lastCommandRun;
        InteractionType copiedByCommandType;

        void constructCommands();
        void parseInputSequence(const std::vector<int> &inputSequence) override;

    public:
        NormalMode(VMModel &model);
        std::pair<InteractionType, std::vector<std::string>> getClipBoard() const;
        const std::vector<int> &getLastInputSequenceBeforeCommandRun() const;
        Command *getLastCommandRun() const;
        void setClipBoard(const std::pair<InteractionType, std::vector<std::string>>& clip);
        const std::pair<bool, char> &getLastFInfo() const;
        void setLastFInfo(const std::pair<bool, char> &lastFInfo);
        void simulateInputSequence(const std::vector<int> &inputSequence, int times);
    };
}

#endif //VM_NORMALMODE_H
