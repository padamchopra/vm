#include "History.h"
#include <utility>
#include "WindowState.h"

double VM::History::timeDifference() const {
    time_t now;
    time(&now);
    return difftime(now, createdAt);
}

VM::History::History(VM::WindowState &state): lines{state.getLines()}, offset{state.getOffset()}, cursor{state.getCursor()} {
    time(&createdAt);
}

const std::vector<std::string> &VM::History::getLines() const {
    return lines;
}

int VM::History::getOffset() const {
    return offset;
}

const std::pair<int, int> &VM::History::getCursor() const {
    return cursor;
}
