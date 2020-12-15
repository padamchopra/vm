#include "WindowState.h"
#include <utility>
#include "../utility/FileManager.h"
#include "../controller/TerminalController.h"

void VM::WindowState::initialise() {
    if (lines.empty()) {
        lines.emplace_back("");
    }
    lastSavedAt = 1;
    offset = 0;
    cursor.first = 0;
    cursor.second = 0;
}

VM::WindowState::WindowState() {
    fileName = "";
    initialise();
}

VM::WindowState::WindowState(const std::string& fileName) : fileName(fileName) {
    try {
        lines = FileManager::readFromFile(fileName);
    } catch (...) {
        FileManager::createFile(fileName);
    }
    initialise();
}

int VM::WindowState::getOffset() const {
    return offset;
}

void VM::WindowState::setOffset(int o) {
    offset = o;
}

const std::pair<int, int> &VM::WindowState::getCursor() const {
    return cursor;
}

void VM::WindowState::setCursor(const std::pair<int, int> &p) {
    cursor = p;
}

const std::string &VM::WindowState::getLine(int lineNumber) const {
    return lines.at(lineNumber);
}

const std::string &VM::WindowState::getFileName() const {
    return fileName;
}

bool VM::WindowState::isOriginalFile() const {
    return pastTimeline.empty();
}

std::pair<int, int> VM::WindowState::getFileInfo() const {
    size_t characters = 0;
    for (const auto &line: lines) {
        characters += line.length() + 1;
    }
    return {lines.size(), characters};
}

int VM::WindowState::getTotalLines() const {
    return lines.size();
}

void VM::WindowState::memoriseState(TerminalController *controller) {
    controller->clearStatus();
    futureTimeline.clear();
    pastTimeline.emplace_back(std::make_shared<History>(*this));
}

void VM::WindowState::setLine(int lineNumber, const std::string &line) {
    lines.at(lineNumber) = line;
}

void VM::WindowState::addLine(int lineNumber, const std::string &line) {
    lines.insert(lines.begin() + lineNumber, line);
}

void VM::WindowState::removeLine(int lineNumber) {
    lines.erase(lines.begin() + lineNumber);
}

void VM::WindowState::moveCursorVertically(Offset o, TerminalController *controller) {
    if (cursor.first == 0 && o == NEG) {
        return;
    } else if (cursor.first >= getTotalLines() - 1 && o == POS) {
        return;
    } else {
        cursor.first = cursor.first + o;
        int newLength = getLine(cursor.first).length();
        if (newLength == 0) {
            cursor.second = 0;
        } else if (newLength <= cursor.second) {
            cursor.second = newLength - 1;
        }
        recalculateOffset(controller);
    }
}

void VM::WindowState::moveCursorHorizontally(Offset o) {
    int length = getLine(cursor.first).length();
    if (cursor.second == 0 && o == NEG) {
        return;
    } else if ((cursor.second == length - 1 && o == POS) || length == 0) {
        return;
    } else {
        cursor.second = cursor.second + o;
    }
}

void VM::WindowState::moveCursor(Direction d, TerminalController *controller) {
    if (d == UP) {
        moveCursorVertically(NEG, controller);
    } else if (d == DOWN) {
        moveCursorVertically(POS, controller);
    } else if (d == LEFT) {
        moveCursorHorizontally(NEG);
    } else if (d == RIGHT) {
        moveCursorHorizontally(POS);
    }
}

void VM::WindowState::recalculateOffset(TerminalController *controller) {
    if (cursor.first < offset) {
        --offset;
    } else {
        int screenHeight = controller->outputWindowHeight();
        int row = offset;
        int linesNeeded = -1;
        for (int rowsPrintedAsOutput = 0; rowsPrintedAsOutput <= screenHeight && row < getTotalLines(); ++row) {
            int linesItWillTake = controller->linesAsOutput(getLine(row).length());
            if (rowsPrintedAsOutput + linesItWillTake > screenHeight) {
                linesNeeded = linesItWillTake - (screenHeight - rowsPrintedAsOutput);
                break;
            }
            rowsPrintedAsOutput += linesItWillTake;
        }
        if (linesNeeded == -1 && cursor.first > row - 1) {
            ++offset;
        } else if (linesNeeded != -1 && cursor.first == row) {
            offset += linesNeeded;
        }
    }
}

const std::vector<std::string> &VM::WindowState::getLines() const {
    return lines;
}

std::string VM::WindowState::previousState(int times) {
    std::string message;
    if (pastTimeline.empty()) {
        message = "Already at oldest change";
    } else {
        if (times > (int) pastTimeline.size()) times = pastTimeline.size();
        message = "Back at #" + std::to_string(pastTimeline.size())  + " change; ";
        while (times > 0) {
            auto local = pastTimeline.back();
            pastTimeline.pop_back();
            futureTimeline.push_back(local);
            --times;
        }
        History *history = futureTimeline.back().get();
        futureTimeline.push_back(std::make_shared<History>(*this));
        offset = history->getOffset();
        lines = history->getLines();
        cursor = history->getCursor();
        double timeDiff = history->timeDifference();
        message += std::to_string((int) timeDiff) + "s ago";
    }
    return message;
}

std::string VM::WindowState::redoState(int times) {
    std::string message;
    if (futureTimeline.empty()) {
        message = "Already at newest change";
    } else {
        if (times > (int) futureTimeline.size()) times = futureTimeline.size();
        message = "Redid #" + std::to_string(futureTimeline.size())  + " change; ";
        while (times > 0) {
            auto local = futureTimeline.back();
            futureTimeline.pop_back();
            pastTimeline.push_back(local);
            --times;
        }
        History *history = pastTimeline.back().get();
        pastTimeline.push_back(std::make_shared<History>(*this));
        offset = history->getOffset();
        lines = history->getLines();
        cursor = history->getCursor();
        double timeDiff = history->timeDifference();
        message += std::to_string((int) timeDiff) + "s ago";
    }
    return message;
}

void VM::WindowState::revalidateCursorForLine() {
    int length = getLine(cursor.first).length();
    if (length == 0) {
        cursor.second = 0;
    } else if (cursor.second >= length){
        cursor.second = length - 1;
    }
}

bool VM::WindowState::isFileSaved() const {
    return lastSavedAt == (int) pastTimeline.size() + 1;
}

void VM::WindowState::saveFile(const std::string &newName) {
    fileName = newName;
    lastSavedAt = pastTimeline.size() + 1;
    FileManager::writeToFile(fileName, lines);
}
