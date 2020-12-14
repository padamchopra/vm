#ifndef VM_MACROINFO_H
#define VM_MACROINFO_H

#include <cstddef>
#include <string>
#include <vector>

namespace VM {
    class VMModel;
    class MacroInfo {
    private:
        bool valid;
        std::string name;
        std::vector<int> sequence;

    public:
        MacroInfo(VMModel &model, const std::string &name);
        int getLastCharacter();
        bool isEmpty();
        bool isValid() const;
    };
}

#endif //VM_MACROINFO_H
