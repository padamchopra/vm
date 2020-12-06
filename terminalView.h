#ifndef VM_TERMINALVIEW
#define VM_TERMINALVIEW

#include <cstddef>
#include <memory>
#include <string>
#include <fstream>
#include "terminal.h"
#include "windowState.h"

enum Alignment {LEFT = 0, RIGHT = 1};

namespace VM {
    class TerminalView {
        std::shared_ptr<Terminal> terminal;
    
        void fillEmptyLines(WindowState *state) {
            terminal->startColored();
            std::pair<int, int> prevCursorPosition = terminal->getCursor();
            int heightAfterPrinting = prevCursorPosition.first;
            int maxHeight = terminal->getScreenSize().first;
            
            while (heightAfterPrinting < maxHeight - 1) {
                terminal->printString("\n~");
                ++heightAfterPrinting;
            }
            terminal->moveCursor(prevCursorPosition);
            terminal->stopColored();
        }

        public:
            TerminalView(std::shared_ptr<Terminal> terminal): terminal{terminal} {}

            void update(WindowState *state) {
                const std::string &content = state->getContent();
                terminal->printString(content);
                fillEmptyLines(state);
                state->setCursorMax(terminal->getCursor());
                terminal->moveCursor(state->getCursor());
            }

            void updateStatus(WindowState *state) {
                if (state->getFileName() != "") {
                    updateStatus("\"" + state->getFileName() + "\"", LEFT);
                    std::pair<int, int> rowColumn = state->getCursorMax();
                    std::string coordinates = "[" + std::to_string(rowColumn.first+1) + "L, " + std::to_string(rowColumn.second+1) + "C]";
                    updateStatus(coordinates, RIGHT);
                }
            }

            void updateStatus(const std::string &message, Alignment align) {
                std::pair<int, int> prevCursorPosition = terminal->getCursor();
                std::pair<int, int> newCursorPositon = terminal->getScreenSize();
                switch (align) {
                    case RIGHT:
                        newCursorPositon.second = newCursorPositon.second - message.length();
                        break;
                    case LEFT:
                    default:
                        newCursorPositon.second = 0;
                }
                terminal->moveCursor(newCursorPositon);
                terminal->printString(message);
                terminal->moveCursor(prevCursorPosition);
            }

    };
}
#endif
