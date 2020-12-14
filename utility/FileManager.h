#ifndef VM_FILEMANAGER_H
#define VM_FILEMANAGER_H

#include <vector>
#include <cstddef>
#include <string>
#include <fstream>

namespace VM {
    class FileManager {
    public:
        static const std::string searchFile;
        static const std::string macrosFile;
        static std::vector<std::string> readFromFile(const std::string &fileName);
        static void writeToFile(const std::string &fileName, std::vector<std::string> &lines);
        static void createFile(const std::string &fileName);
        static void log(std::string &message);
    };
}

#endif //VM_FILEMANAGER_H
