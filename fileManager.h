#ifndef VM_FILEMANAGER
#define VM_FILEMANAGER

#include <ncurses.h>
#include <cstddef>
#include <string>
#include <fstream>

namespace VM {
    class FileManager {
        public:
            static std::string readFromFile(std::string &fileName) {
                std::ifstream file{fileName};
                std::string content = "";
                if (file.is_open()) {
                    std::string line;

                    while (std::getline(file, line)) {
                        content += line + "\n";
                    }
                    file.close();
                    return content;
                } else {
                    throw -1;
                }
            }

            static void writeToFile(std::string &fileName, std::string &message) {
                std::ofstream file{fileName};
                file << message;
                file.close();
            }


            //TODO: remove this
            static void log(std::string &message) {
                std::ofstream outfile;
                outfile.open("debug.txt", std::ios_base::app);
                outfile << message << "\n"; 
            }

            static void createFile(std::string &fileName) {
                std::ofstream file{fileName};
                file.close();
            }
    };
}

#endif