#include "NormalMode.h"
#include "../model/VMModel.h"
#include "../commands/motion/J.h"
#include "../commands/motion/K.h"
#include "../commands/motion/H.h"
#include "../commands/motion/L.h"
#include "../commands/insert/I.h"
#include "../commands/insert/A.h"
#include "../commands/motion/B.h"
#include "../commands/editing/CC.h"
#include "../commands/cutpaste/DD.h"
#include "../commands/motion/F.h"
#include "../commands/motion/N.h"
#include "../commands/insert/O.h"
#include "../commands/cutpaste/P.h"
#include "../commands/editing/R.h"
#include "../commands/editing/S.h"
#include "../commands/editing/U.h"
#include "../commands/motion/W.h"
#include "../commands/cutpaste/X.h"
#include "../commands/cutpaste/YY.h"
#include "../commands/insert/CapA.h"
#include "../commands/motion/CapF.h"
#include "../commands/insert/CapI.h"
#include "../commands/editing/CapJ.h"
#include "../commands/motion/CapN.h"
#include "../commands/insert/CapO.h"
#include "../commands/cutpaste/CapP.h"
#include "../commands/insert/CapR.h"
#include "../commands/editing/CapS.h"
#include "../commands/cutpaste/CapX.h"
#include "../commands/motion/Carrot.h"
#include "../commands/motion/Dollar.h"
#include "../commands/motion/Zero.h"
#include "../commands/motion/SemiColon.h"
#include "../commands/editing/SwitchEx.h"
#include "../commands/motion/ControlB.h"
#include "../commands/motion/ControlF.h"
#include "../commands/motion/ControlD.h"
#include "../commands/motion/ControlU.h"
#include "../commands/motion/ControlG.h"
#include "../commands/editing/ControlR.h"
#include "../commands/motion/Slash.h"
#include "../commands/motion/Question.h"
#include "../commands/editing/Dot.h"
#include "../commands/macro/MacroQ.h"
#include "../commands/macro/MacroAt.h"

void VM::NormalMode::constructCommands() {
    commands.emplace_back(std::make_unique<J>());
    commands.emplace_back(std::make_unique<K>());
    commands.emplace_back(std::make_unique<H>());
    commands.emplace_back(std::make_unique<L>());
    commands.emplace_back(std::make_unique<I>());
    commands.emplace_back(std::make_unique<A>());
    commands.emplace_back(std::make_unique<B>());
    commands.emplace_back(std::make_unique<CC>());
    commands.emplace_back(std::make_unique<DD>());
    commands.emplace_back(std::make_unique<F>());
    commands.emplace_back(std::make_unique<N>());
    commands.emplace_back(std::make_unique<O>());
    commands.emplace_back(std::make_unique<P>());
    commands.emplace_back(std::make_unique<R>());
    commands.emplace_back(std::make_unique<S>());
    commands.emplace_back(std::make_unique<U>());
    commands.emplace_back(std::make_unique<W>());
    commands.emplace_back(std::make_unique<X>());
    commands.emplace_back(std::make_unique<YY>());
    commands.emplace_back(std::make_unique<CapA>());
    commands.emplace_back(std::make_unique<CapF>());
    commands.emplace_back(std::make_unique<CapI>());
    commands.emplace_back(std::make_unique<CapJ>());
    commands.emplace_back(std::make_unique<CapN>());
    commands.emplace_back(std::make_unique<CapO>());
    commands.emplace_back(std::make_unique<CapP>());
    commands.emplace_back(std::make_unique<CapR>());
    commands.emplace_back(std::make_unique<CapS>());
    commands.emplace_back(std::make_unique<CapX>());
    commands.emplace_back(std::make_unique<Carrot>());
    commands.emplace_back(std::make_unique<Dollar>());
    commands.emplace_back(std::make_unique<SemiColon>());
    commands.emplace_back(std::make_unique<SwitchEx>());
    commands.emplace_back(std::make_unique<Zero>());
    commands.emplace_back(std::make_unique<ControlB>());
    commands.emplace_back(std::make_unique<ControlF>());
    commands.emplace_back(std::make_unique<ControlD>());
    commands.emplace_back(std::make_unique<ControlU>());
    commands.emplace_back(std::make_unique<ControlG>());
    commands.emplace_back(std::make_unique<ControlR>());
    commands.emplace_back(std::make_unique<Slash>());
    commands.emplace_back(std::make_unique<Question>());
    commands.emplace_back(std::make_unique<Dot>());
    commands.emplace_back(std::make_unique<MacroQ>());
    commands.emplace_back(std::make_unique<MacroAt>());
}

void VM::NormalMode::parseInputSequence(const std::vector<int> &inputSequence) {
    for (const auto &command : commands) {
        int count = command->isAMatch(inputSequence);
        if (count != 0) {
            if (command->isUndoable()) {
                lastCommandRun = command.get();
                lastInputSequenceBeforeCommandRun = inputSequence;
            }
            if (!command->isRecordable()) {
                model.partlyEraseRecordingSequence(inputSequence);
            }
            command->execute(model, count);
            break;
        }
    }
}

VM::NormalMode::NormalMode(VM::VMModel &model) : Mode(model), copiedByCommandType{ALL} {
    clipBoard.clear();
    clipBoard.emplace_back("");
    lastFInfo = {true, '\0'};
    constructCommands();
}

std::pair<InteractionType, std::vector<std::string>> VM::NormalMode::getClipBoard() const {
    return {copiedByCommandType, clipBoard};
}

void VM::NormalMode::setClipBoard(const std::pair<InteractionType, std::vector<std::string>>& clip) {
    clipBoard = clip.second;
    copiedByCommandType = clip.first;
}

const std::pair<bool, char> &VM::NormalMode::getLastFInfo() const {
    return lastFInfo;
}

void VM::NormalMode::setLastFInfo(const std::pair<bool, char> &currentFInfo) {
    lastFInfo = currentFInfo;
}

const std::vector<int> &VM::NormalMode::getLastInputSequenceBeforeCommandRun() const {
    return lastInputSequenceBeforeCommandRun;
}

VM::Command *VM::NormalMode::getLastCommandRun() const {
    return lastCommandRun;
}

void VM::NormalMode::simulateInputSequence(const std::vector<int> &inputSequence, int times) {
    for (const auto &command : commands) {
        int count = command->isAMatch(inputSequence);
        if (count != 0) {
            command->execute(model, times);
            break;
        }
    }
}
