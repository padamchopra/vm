#include "Terminal.h"

VM::Terminal::Terminal() {
    initscr();
    use_default_colors();
    raw();
    noecho();
    getmaxyx(stdscr, screenSize.first, screenSize.second);
    WINDOW *fileWindow = newwin(screenSize.first - 1, screenSize.second, 0, 0);
    keypad(fileWindow, true);
    scrollok(fileWindow, true);
    WINDOW  *statusbar = newwin(1, screenSize.second, screenSize.first - 1, 0);
    keypad(statusbar, true);
    refresh();
    windows.push_back(fileWindow);
    windows.push_back(statusbar);
}

int VM::Terminal::getKeyStroke(TerminalWindow w) {
    return wgetch(windows.at(w));
}

void VM::Terminal::printString(TerminalWindow w, const std::string &s) {
    if (s.length() == 0) {
        wdelch(windows.at(w));
    } else {
        waddstr(windows.at(w), s.c_str());
    }
    wrefresh(windows.at(w));
}

int VM::Terminal::linesOccupied(int length) {
    if (length < screenSize.second) {
        return 1;
    } else {
        int result = 0;
        while (length > 0) {
            result++;
            length = length - screenSize.second;
        }
        return result;
    }
}

std::pair<int, int> VM::Terminal::getCursorFromTerminal(TerminalWindow w) {
    std::pair<int, int> position;
    getyx(windows.at(w), position.first, position.second);
    return position;
}

void VM::Terminal::moveCursorInTerminal(TerminalWindow w, const std::pair<int, int> &position) {
    wmove(windows.at(w), position.first, position.second);
    wrefresh(windows.at(w));
}

std::pair<int, int> VM::Terminal::getWindowSize(TerminalWindow w) const {
    if (w == FILEWINDOW) {
        return {screenSize.first - 1, screenSize.second};
    } else if (w == STATUSBAR) {
        return {1, screenSize.second};
    }
    return screenSize;
}

void VM::Terminal::startColoredOutput(TerminalWindow w) {
    if (has_colors()) {
        start_color();
        init_pair(blueTextPair, COLOR_BLUE, -1);
        wattron(windows.at(w), COLOR_PAIR(blueTextPair));
    }
}

void VM::Terminal::stopColoredOutput(TerminalWindow w) {
    if (has_colors()) {
        wattroff(windows.at(w), COLOR_PAIR(blueTextPair));
    }
}

void VM::Terminal::clear(TerminalWindow w) {
    wclear(windows.at(w));
    wrefresh(windows.at(w));
}


void VM::Terminal::clear() {
    for(WINDOW *w: windows) {
        wclear(w);
        wrefresh(w);
    }
}

void VM::Terminal::startErrorOutput(TerminalWindow w) {
    if (has_colors()) {
        start_color();
        init_pair(redTextPair, COLOR_WHITE, COLOR_RED);
        wattron(windows.at(w), COLOR_PAIR(redTextPair));
    }
}

void VM::Terminal::stopErrorOutput(TerminalWindow w) {
    if (has_colors()) {
        wattroff(windows.at(w), COLOR_PAIR(redTextPair));
    }
}

VM::Terminal::~Terminal() {
    endwin();
}
