#include "SemiColon.h"
#include "../../model/VMModel.h"
#include "../../mode/NormalMode.h"
#include "F.h"
#include "CapF.h"

void VM::SemiColon::executeFor(VM::VMModel &model, int times) {
    auto *mode = dynamic_cast<NormalMode*>(model.getMode(NORMAL_MODE));
    if (mode != nullptr) {
        std::pair<bool, char> fInfo = mode->getLastFInfo();
        if (fInfo.second != '\0') {
            if (fInfo.first) {
                F f{fInfo.second};
                f.execute(model, times);
            } else {
                CapF f{fInfo.second};
                f.execute(model, times);
            }
        }
    }
}

VM::SemiColon::SemiColon() {
    commandSequence.push_back(';');
}
