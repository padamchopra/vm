#ifndef VM_INSERTMODE_H
#define VM_INSERTMODE_H


#include "Mode.h"

namespace VM {
    class InsertMode: public Mode {
    private:
        std::vector<int> sequence;
        bool enterAtEnd;
        bool replaceMode;
        int lastCalledWithCount;
        void parseInputSequence(const std::vector<int> &inputSequence) override;
        void makeChanges(int key, bool calledFromILoop);
        void handleBackspace();
        void handleCharacterPrint(int key);

    public:
        InsertMode(VMModel &model);
        void setReplaceMode(bool replaceMode);
        void setEnterAtEnd(bool enterAtEnd);
        void setCountForCall(int num);
        void executeRecordedSequence();
        void makeExitPreparations();
        void clearSequence();

        void setSequence(const std::vector<int> &sequence);

        const std::vector<int> &getSequence() const;
    };
}


#endif //VM_INSERTMODE_H
