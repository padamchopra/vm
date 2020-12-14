#include "MacroInfo.h"
#include <utility>
#include "../model/VMModel.h"
#include "FileManager.h"
#include <algorithm>

VM::MacroInfo::MacroInfo(VM::VMModel &model, const std::string &name) : name{name} {
    std::vector<std::string> lines;
    valid = false;
    try {
        bool exists = false;
        lines = FileManager::readFromFile(FileManager::macrosFile);
        std::string macroLine;
        for (size_t i = 0; i < lines.size(); i = i + 2) {
            if (lines.at(i) == name) {
                macroLine = lines.at(i + 1);
                exists = true;
                break;
            }
        }
        if (!exists) {
            model.updateStatusWithError("macro \"" + name + "\" does not exist");
        } else {
            sequence.clear();
            std::string intCode;
            for (size_t i = 0; i <macroLine.size(); ++i) {
                if (macroLine.at(i) == ' ') {
                    sequence.push_back(std::stoi(intCode));
                    intCode = "";
                } else {
                    intCode += macroLine.at(i);
                }
            }
            std::reverse(sequence.begin(), sequence.end());
            valid = true;
        }
    } catch (...) {
        model.updateStatusWithError("macro \"" + name + "\" does not exist");
    }
}

int VM::MacroInfo::getLastCharacter() {
    int c = 0;
    if (!sequence.empty()) {
        c = sequence.back();
        sequence.pop_back();
    }
    return c;
}

bool VM::MacroInfo::isEmpty() {
    return sequence.empty();
}

bool VM::MacroInfo::isValid() const {
    return valid;
}
