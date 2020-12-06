#ifndef VM_WINDOWSTATE
#define VM_WINDOWSTATE

#include <iostream>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "display.h"
#include "fileManager.h"

namespace VM {
    class WindowState {
        private:
            std::pair<int, int> cursor;
            std::pair<int, int> maxCursor;
            std::vector<std::unique_ptr<Display>> timeline;
            std::string content;
            std::string fileName;

            void initialise() {
                cursor.first = 0;
                cursor.second = 0;
            }

        public:
            WindowState() {
                fileName = "";
                content = "";
                initialise();
            }

            WindowState(std::string fileName): fileName{fileName} {
                try {
                    content = FileManager::readFromFile(fileName);
                    if (!content.empty() && content[content.length() - 1] == '\n') {
                        content.erase(content.length()-1);
                    }
                } catch (...) {
                    FileManager::createFile(fileName);
                    content = "";
                }
                initialise();
            }

            const std::string &getContent() const {
                return content;
            }

            const std::string &getFileName() const {
                return fileName;
            }

            std::pair<int, int> getCursor() const {
                return cursor;
            }
            
            void setCursor(std::pair<int, int> position) {
                cursor = position;
            }

            std::pair<int, int> getCursorMax() const {
                return maxCursor;
            }

            void setCursorMax(std::pair<int, int> maxPosition) {
                maxCursor = maxPosition;
            }
            
    };

    std::ostream &operator<<(std::ostream &out, const WindowState &state);
}

#endif
