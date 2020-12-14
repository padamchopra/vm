#ifndef VM_CONTROLLER_H
#define VM_CONTROLLER_H


#include <memory>
#include <utility>
#include <vector>

namespace VM {
    class Terminal;
    class Controller {
    private:
        std::vector<int> input;
        virtual int getKeyPress() const = 0;
        virtual void doClearStatus() const = 0;

    protected:
        std::shared_ptr<Terminal> terminal;

    public:
        Controller(std::shared_ptr<Terminal> terminal) : terminal(std::move(terminal)) {}
        virtual ~Controller() = default;

        const std::vector<int> &getInput() {
            input.push_back(getKeyPress());
            return input;
        }

        void popLastInput() {
            if (!input.empty()) {
                input.pop_back();
            }
        }

        void resetInput() noexcept {
            input.clear();
        }

        void clearStatus() {
            doClearStatus();
        }
    };
}

#endif //VM_CONTROLLER_H
