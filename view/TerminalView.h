#ifndef VM_TERMINALVIEW_H
#define VM_TERMINALVIEW_H


#include "View.h"

namespace VM {
    class TerminalView: public View {
    private:
        void drawEmptyLines();
        void updateView(WindowState *state) override;
        void repositionCursor(WindowState *state);
    public:
        TerminalView(std::shared_ptr<Terminal> terminal);
    };
}

#endif //VM_TERMINALVIEW_H
