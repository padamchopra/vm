#ifndef VM_MODEL
#define VM_MODEL

#include <iostream>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "windowState.h"
#include "terminal.h"
#include "terminalController.h"
#include "terminalView.h"

enum specialInputs {CTRL_C = 3};

namespace VM {
    class VMModel {
        size_t currentActiveState;
        std::vector<std::unique_ptr<WindowState>> states;
        std::shared_ptr<Terminal> terminal;
        std::unique_ptr<TerminalController> controller;
        std::unique_ptr<TerminalView> view;
        bool keepRunning;
        bool passInputToMode;

        private:
            void addState(const std::string &fileName) {
                if (fileName == "") {
                    states.emplace_back(std::make_unique<WindowState>());
                } else {
                    states.emplace_back(std::make_unique<WindowState>(fileName));
                }
            }

            void handleInteractions() {
                char c = controller->getKeyPress();
                switch (c) {
                    case CTRL_C:
                        stop();
                        break;
                    default:
                        std::string &command = controller->getCommand();
                        terminal->printString(command);
                };
            }

        public:
            VMModel(size_t fileCount, char *fileNames[]) {
                currentActiveState = 0;
                terminal = std::make_shared<Terminal>();
                controller = std::make_unique<TerminalController>(terminal);
                view = std::make_unique<TerminalView>(terminal);

                if (fileCount == 0) {
                    addState("");
                } else {
                    for (size_t i = 0; i < fileCount; ++i) {
                        std::string fileName = fileNames[i+1];
                        addState(fileName);
                    }
                }

            }

            void start() {
                keepRunning = true;
                passInputToMode = true;

                updateViews();

                while (keepRunning) {
                    handleInteractions();
                }
            }

            void updateViews() {
                view->update(getActiveState());   
                view->updateStatus(getActiveState());
            }

            void stop() {
                keepRunning = false;
                passInputToMode = false;
            }

            WindowState *getActiveState() {
                return states[currentActiveState].get();
            }

            void setActiveState(size_t index) {
                if (index < states.size()) {
                    currentActiveState = index;
                } else {
                    throw -1;
                }
            }
    };

    std::ostream &operator<<(std::ostream &out, const VMModel &model);
}

#endif
