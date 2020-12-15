#ifndef VM_MODEL_H
#define VM_MODEL_H

#include <cstddef>
#include <vector>
#include <string>
#include <memory>
#include "../view/View.h"
#include "../controller/Controller.h"
#include "../state/WindowState.h"

namespace VM {
    class Model {
    private:
        size_t currentView;
        std::vector<std::unique_ptr<View>> views;

    protected:
        std::unique_ptr<Controller> controller;
        void addView(View *view);

    public:
        Model();
        virtual const std::vector<int> &getInput();
        void updateView(WindowState *state);
        virtual void updateStatus(const std::string &message);
        void updateStatusWithError(const std::string &message);
    };
}


#endif //VM_MODEL_H
