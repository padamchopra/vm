#include "Question.h"
#include "../../model/VMModel.h"
#include "../../controller/TerminalController.h"
#include "../../utility/FileManager.h"
#include "N.h"

VM::Question::Question() {
    commandSequence.push_back('?');
}

void VM::Question::executeFor(VM::VMModel &model, int times) {
    model.clearInputSequence();
    TerminalController *controller = model.getController();
    controller->clearStatus();
    int lastEntered = '?';
    std::string toPrint;
    while (lastEntered != ENTER) {
        if (lastEntered != LARROW && lastEntered != RARROW && lastEntered != DARROW && lastEntered != UARROW) {
            if (lastEntered == BACKSPACE) {
                if (toPrint.size() == 1) {
                    model.updateStatus("");
                    return;
                } else {
                    toPrint = toPrint.substr(0, toPrint.size() - 1);
                    model.updateStatus(toPrint);
                    controller->positionCursorAtStatus(toPrint.size());
                }
            } else {
                toPrint += (char) lastEntered;
                model.updateStatus(toPrint);
                controller->positionCursorAtStatus(toPrint.size());
            }
        }
        lastEntered = model.getInput().back();
    }
    if (toPrint.size() > 1) {
        toPrint = std::to_string(BACKWARD) + toPrint.substr(1);
        std::vector<std::string> lines;
        lines.emplace_back(toPrint);
        FileManager::writeToFile(FileManager::searchFile, lines);
        N n{};
        n.execute(model, times);
    }
}
