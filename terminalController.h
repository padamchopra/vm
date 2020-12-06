#ifndef VM_TERMINALCONTROLLER
#define VM_TERMINALCONTROLLER

#include <cstddef>
#include <memory>
#include <string>
#include <fstream>
#include "terminal.h"

namespace VM {
    class TerminalController {
        std::shared_ptr<Terminal> terminal;
        std::string command;

        public:
            TerminalController(std::shared_ptr<Terminal> terminal): terminal{terminal} {
                command = "";
            }

            char getKeyPress() {
                char c = terminal->getInputKeyStroke();
                command += c;
                return c;
            } 

            std::string &getCommand() {
                return command;
            }

            void resetCommand() {
                command = "";
            }


    };
}
#endif
