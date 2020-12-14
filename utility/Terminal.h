#ifndef VM_TERMINAL_H
#define VM_TERMINAL_H

#include <ncurses.h>
#include <vector>
#include <string>

enum TerminalWindow {FILEWINDOW = 0, STATUSBAR = 1};

namespace VM {
    class Terminal {
    private:
        std::pair<int, int> screenSize;
        std::vector<WINDOW *> windows;
        short blueTextPair = 1;
        short redTextPair = 2;

    public:
        Terminal();
        int getKeyStroke(TerminalWindow w);
        void printString(TerminalWindow w, const std::string &s);
        int linesOccupied(int length);
        std::pair<int, int> getCursorFromTerminal(TerminalWindow w);
        void moveCursorInTerminal(TerminalWindow w, const std::pair<int, int> &position);
        std::pair<int, int> getWindowSize(TerminalWindow w) const;
        void startColoredOutput(TerminalWindow w);
        void stopColoredOutput(TerminalWindow w);
        void startErrorOutput(TerminalWindow w);
        void stopErrorOutput(TerminalWindow w);
        void clear(TerminalWindow w);
        void clear();
        ~Terminal();
    };
}

#endif //VM_TERMINAL_H
