#ifndef VM_WINDOWSTATE_H
#define VM_WINDOWSTATE_H

#include <vector>
#include <string>
#include <memory>
#include "History.h"

enum Offset{NEG = -1, POS = 1};
enum Direction{UP, DOWN, LEFT, RIGHT};
namespace VM {
    class TerminalController;
    class WindowState {
    private:
        int offset;
        int lastSavedAt;
        std::pair<int, int> cursor;
        std::vector<std::shared_ptr<History>> pastTimeline;
        std::vector<std::shared_ptr<History>> futureTimeline;
        std::vector<std::string> lines;
        std::string fileName;
        void initialise();
        void moveCursorVertically(Offset o, TerminalController *controller);
        void moveCursorHorizontally(Offset o);
        void recalculateOffset(TerminalController *controller);

    public:
        WindowState();
        WindowState(const std::string& fileName);
        const std::vector<std::string> &getLines() const;
        const std::string &getLine(int lineNumber) const;
        void setLine(int lineNumber, const std::string &line);
        void addLine(int lineNumber, const std::string &line);
        void removeLine(int lineNumber);
        bool isOriginalFile() const;
        void saveFile(const std::string &newName);
        bool isFileSaved() const;
        int getTotalLines() const;
        void memoriseState(TerminalController *controller);
        std::string redoState(int times);
        std::string previousState(int times);
        std::pair<int, int> getFileInfo() const;
        const std::string &getFileName() const;
        int getOffset() const;
        void setOffset(int o);
        const std::pair<int, int> &getCursor() const;
        void moveCursor(Direction d, TerminalController *controller);
        void setCursor(const std::pair<int, int> &p);
        void revalidateCursorForLine();
    };
}

#endif //VM_WINDOWSTATE_H
