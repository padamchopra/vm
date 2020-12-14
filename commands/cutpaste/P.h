#ifndef VM_P_H
#define VM_P_H


#include "CutPasteCommand.h"

namespace VM {
    class P: public CutPasteCommand {
    private:
        bool beforeCursor;
        void executeFor(VMModel &model, int times) override;
        void executeOnceForAll(VMModel &model, const std::vector<std::string> &lines);
        void executeOnceForLine(VMModel &model, const std::vector<std::string> &lines);

    public:
        P();
        P(bool canUndo, bool before);
    };
}


#endif //VM_P_H
