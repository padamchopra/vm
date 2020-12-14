#include "FileManager.h"

const std::string VM::FileManager::searchFile = "./.searchHistory.txt";
const std::string VM::FileManager::macrosFile = "./.vmMacros.txt";

std::vector<std::string> VM::FileManager::readFromFile(const std::string &fileName) {
    std::ifstream file{fileName};
    std::vector<std::string> lines;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
        return lines;
    } else {
        throw std::exception();
    }
}

void VM::FileManager::writeToFile(const std::string &fileName, std::vector<std::string> &lines) {
    std::ofstream file{fileName};
    for (const auto &line : lines) {
        file << line << "\n";
    }
    file.close();
}

void VM::FileManager::createFile(const std::string &fileName) {
    std::ofstream file{fileName};
    file.close();
}

void VM::FileManager::log(std::string &message) {
    std::ofstream outfile;
    outfile.open("debug.txt", std::ios_base::app);
    outfile << message << "\n";
}
