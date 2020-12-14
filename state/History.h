#ifndef VM_HISTORY_H
#define VM_HISTORY_H

#include <ctime>
#include <vector>
#include <string>

namespace VM {
    class WindowState;
    class History {
    private:
        std::vector<std::string> lines;
        int offset;
        std::pair<int, int> cursor;
        time_t createdAt;

    public:
        History(WindowState &state);
        const std::vector<std::string> &getLines() const;
        int getOffset() const;
        const std::pair<int, int> &getCursor() const;
        double timeDifference() const;
    };
}

#endif //VM_HISTORY_H
