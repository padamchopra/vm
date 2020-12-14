#ifndef VM_TERMINALCONTROLLER_H
#define VM_TERMINALCONTROLLER_H


#include "Controller.h"

namespace VM {
    class Terminal;
    class TerminalController: public Controller {
    private:
        int getKeyPress() const override;
        void doClearStatus() const override;
    public:
        TerminalController(const std::shared_ptr<Terminal> &terminal);
        int linesAsOutput(int length) const;
        int outputWindowHeight() const;
        void positionCursorAtStatus(int x);
    };
}

#endif //VM_TERMINALCONTROLLER_H
