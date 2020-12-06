#ifndef VM_TERMINAL
#define VM_TERMINAL

#include <ncurses.h>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace VM {
    class Terminal {
        private:
            std::pair<int, int> screenSize;

        public:
            Terminal() {
                initscr();
                use_default_colors();
                raw();
                noecho();
                keypad(stdscr, true);
                scrollok(stdscr, true);
                getmaxyx(stdscr, screenSize.first, screenSize.second);
                screenSize.first = screenSize.first - 1;
                screenSize.second = screenSize.second - 1;
            }

            char getInputKeyStroke() {
                return getch();
            }

            void printCharacter(char c) {
                addch(c);
                refresh();
            }

            void printString(const std::string &s) {
                addstr(s.c_str());
                refresh();
            }

            std::pair<int, int> getCursor() {
                std::pair<int, int> position;
                getyx(stdscr, position.first, position.second);
                return position;
            }

            void moveCursor(std::pair<int, int> position) {
                move(position.first, position.second);
            }

            std::pair<int, int> getScreenSize() const {
                return screenSize;
            }

            void startColored() {
                if (has_colors()) {
                    start_color();
                    init_pair(1, COLOR_BLUE, -1);
                    attron(COLOR_PAIR(1));
                }
            }

            void stopColored() {
                if (has_colors()) {
                    attroff(COLOR_PAIR(1));
                }
            }

            //TODO: remove this
            std::string pairToString(std::pair<int, int> posn) {
                std::string message = "[" + std::to_string(posn.first) + ", " + std::to_string(posn.second) + "]";
                return message;
            }

            ~Terminal() {
                endwin();
            }
    };
}
#endif
