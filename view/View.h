#ifndef VM_VIEW_H
#define VM_VIEW_H

#include <memory>
#include <utility>
#include <string>
#include "../utility/Terminal.h"
#include "../state/WindowState.h"

namespace VM {
    class View {
    private:
        virtual void updateView(WindowState *state) = 0;

    protected:
        std::shared_ptr<Terminal> terminal;

    public:
        View(std::shared_ptr<Terminal> terminal) : terminal(std::move(terminal)) {}
        virtual ~View() = default;

        void update(WindowState *state) {
            terminal->clear(FILEWINDOW);
            updateView(state);
        }

        void updateStatus(const std::string &message) {
            std::pair<int, int> prevPosition = terminal->getCursorFromTerminal(FILEWINDOW);
            terminal->clear(STATUSBAR);
            terminal->printString(STATUSBAR, message);
            terminal->moveCursorInTerminal(FILEWINDOW, prevPosition);
        }
    };
}

#endif //VM_VIEW_H
