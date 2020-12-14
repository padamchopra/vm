#ifndef VM_MODE_H
#define VM_MODE_H

#include <vector>

namespace VM {
    class VMModel;

    class Mode {
    private:
        virtual void parseInputSequence(const std::vector<int> &inputSequence) = 0;

    protected:
        VMModel &model;

    public:
        Mode(VMModel &model): model{model} {}
        virtual ~Mode() = default;

        void parseInput(const std::vector<int> &inputSequence) {
            parseInputSequence(inputSequence);
        }
    };
}


#endif //VM_MODE_H
