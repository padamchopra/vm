#include "ExMode.h"
#include "../model/VMModel.h"
#include "../controller/TerminalController.h"
#include "../commands/ex/ExW.h"
#include "../commands/ex/ExQ.h"
#include "../commands/ex/ExWQ.h"
#include "../commands/ex/ExQExclamation.h"
#include "../commands/ex/ExR.h"
#include "../commands/ex/ExZero.h"
#include "../commands/ex/ExDollar.h"
#include "../commands/ex/ExLineNumber.h"
#include "../commands/ex/ExN.h"
#include "../commands/ex/ExPrev.h"
#include "../commands/ex/ExAuth.h"
#include "../commands/ex/ExE.h"

void VM::ExMode::constructCommands() {
    commands.push_back(std::make_unique<ExW>());
    commands.push_back(std::make_unique<ExQ>());
    commands.push_back(std::make_unique<ExWQ>());
    commands.push_back(std::make_unique<ExQExclamation>());
    commands.push_back(std::make_unique<ExR>());
    commands.push_back(std::make_unique<ExZero>());
    commands.push_back(std::make_unique<ExDollar>());
    commands.push_back(std::make_unique<ExLineNumber>());
    if (model.isEnhanced()) {
        commands.push_back(std::make_unique<ExE>());
        commands.push_back(std::make_unique<ExN>());
        commands.push_back(std::make_unique<ExPrev>());
        commands.push_back(std::make_unique<ExAuth>());
    }
}

VM::ExMode::ExMode(VM::VMModel &model) : Mode(model) {
    constructCommands();
}

void VM::ExMode::parseInputSequence(const std::vector<int> &inputSequence) {
    if (inputSequence.back() == LARROW || inputSequence.back() == RARROW || inputSequence.back() == UARROW || inputSequence.back() == DARROW) {
        return;
    }
    if (inputSequence.back() == ENTER) {
        bool executedSomething = false;
        for (const auto &command : commands) {
            bool result = command->isAMatch(inputSequence);
            if (result) {
                executedSomething = true;
                std::vector<int> sequence = inputSequence;
                sequence.pop_back();
                command->execute(model, sequence);
                break;
            }
        }
        if (!executedSomething) {
            model.updateStatusWithError("Not an editor command.");
        }
        prepareForExit();
    } else if (inputSequence.back() == ESC) {
        prepareForExit();
    } else {
        if (inputSequence.back() == BACKSPACE) {
            model.getController()->popLastInput();
            model.getController()->popLastInput();
        }
        if (inputSequence.empty()) {
            model.getController()->clearStatus();
            prepareForExit();
        } else {
            TerminalController *controller = model.getController();
            controller->clearStatus();
            std::string message = ":";
            for (int c: inputSequence) {
                message += (char) c;
            }
            model.updateStatus(message);
            controller->positionCursorAtStatus(message.length());
        }
    }
}

void VM::ExMode::prepareForExit() {
    model.clearInputSequence();
    model.changeMode(NORMAL_MODE);
    model.updateView(model.getActiveState());
}
