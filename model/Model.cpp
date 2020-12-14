#include "Model.h"

VM::Model::Model() {
    currentView = 0;
    terminal = std::make_shared<Terminal>();
}

void VM::Model::addView(View *view) {
    views.emplace_back(std::unique_ptr<View>(view));
}

void VM::Model::updateView(WindowState *state) {
    views.at(currentView)->update(state);
}

void VM::Model::updateStatus(const std::string &message) {
    views.at(currentView)->updateStatus(message);
}

const std::vector<int> &VM::Model::getInput() {
    return controller->getInput();
}

void VM::Model::updateStatusWithError(const std::string &message) {
    terminal->startErrorOutput(STATUSBAR);
    updateStatus(message);
    terminal->stopErrorOutput(STATUSBAR);
}
