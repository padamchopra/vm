#ifndef VM_DISPLAY
#define VM_DISPLAY

#include <iostream>
#include <cstddef>
#include <memory>
#include <string>
#include <ctime>

namespace VM {
    class Display {
        std::string content;
        time_t createdAt;

        public:
            Display(std::string content): content{content} {
                time(&createdAt);
            }

            double timeDifference() {
                time_t now;
                time(&now);
                return difftime(now, createdAt);
            }
            
    };
}
#endif
