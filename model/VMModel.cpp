#include "VMModel.h"
#include "../view/TerminalView.h"
#include "../mode/NormalMode.h"
#include "../mode/InsertMode.h"
#include "../mode/ExMode.h"
#include "../controller/TerminalController.h"
#include "../utility/FileManager.h"

void VM::VMModel::initialise() {
    currentState = 0;
    currentMode = 0;
    controller = std::make_unique<TerminalController>(terminal);
    addView(new TerminalView(terminal));
    modes.emplace_back(std::make_unique<NormalMode>(*this));
    modes.emplace_back(std::make_unique<InsertMode>(*this));
    modes.emplace_back(std::make_unique<ExMode>(*this));
}

void VM::VMModel::addState(const std::string &fileName) {
    if (fileName.empty()) {
        states.emplace_back(std::make_unique<WindowState>());
    } else {
        states.emplace_back(std::make_unique<WindowState>(fileName));
    }
}

VM::VMModel::VMModel(int fileCount, char *fileNames[]): Model{} {
    initialise();
    if (fileCount == 0) {
        addState("");
    } else {
        for (size_t i = 0; i < fileCount; ++i) {
            std::string fileName = fileNames[i+1];
            addState(fileName);
        }
    }
}

void VM::VMModel::start() {
    recording = false;
    keepRunning = true;
    setCurrentState(0);
    while (keepRunning) {
        handleInteractions();
    }
}

void VM::VMModel::handleInteractions() {
    const std::vector<int> &seq = getInput();
    modes.at(currentMode)->parseInput(seq);
}

void VM::VMModel::stop() {
    keepRunning = false;
}

VM::WindowState *VM::VMModel::getActiveState() const {
    return states.at(currentState).get();
}

void VM::VMModel::clearInputSequence() {
    if (playing) {
        inputSimulator.clear();
    }
    controller->resetInput();
}

void VM::VMModel::changeMode(Modes m) {
    if (m == INSERT_MODE) {
        auto *mode = dynamic_cast<InsertMode*>(modes.at(INSERT_MODE).get());
        if (mode != nullptr) {
            mode->clearSequence();
        }
    }
    currentMode = m;
}

VM::Mode *VM::VMModel::getMode(Modes m) {
    return modes.at(m).get();
}

void VM::VMModel::startRecordingSequence(const std::string &name) {
    recordingName = name;
    recording = true;
}

void VM::VMModel::stopRecordingSequence() {
    if (!recording) return;
    recording = false;
    std::string macroLine;
    for (int c: recordingSequence) {
        macroLine += std::to_string(c) + " ";
    }
    std::vector<std::string> lines;
    bool alreadyExists = false;
    try {
        lines = FileManager::readFromFile(FileManager::macrosFile);
        for (int i = 0; i < lines.size(); i = i + 2) {
            if (lines.at(i) == recordingName) {
                lines[i + 1] = macroLine;
                alreadyExists = true;
                break;
            }
        }
    } catch (...) {
        FileManager::createFile(FileManager::macrosFile);
    }
    if (!alreadyExists) {
        lines.push_back(recordingName);
        lines.push_back(macroLine);
    }
    FileManager::writeToFile(FileManager::macrosFile, lines);
    lastPlayedMacro = recordingName;
    recordingName = "";
    recordingSequence.clear();
}

VM::TerminalController *VM::VMModel::getController() const {
    return dynamic_cast<TerminalController*>(controller.get());
}

void VM::VMModel::setCurrentState(size_t i) {
    if (i >= states.size()) i = 0;
    if (i < 0) i = 0;
    currentState = i;
    WindowState *state = getActiveState();
    updateView(state);

    if (!state->getFileName().empty() && state->isOriginalFile()) {
        std::string toPrint = "\"" + state->getFileName() + "\"";
        std::pair<int, int> fileInfo = state->getFileInfo();
        std::string coordinates = std::to_string(fileInfo.first) + "L, " + std::to_string(fileInfo.second) + "C";
        toPrint += " " + coordinates;
        updateStatus(toPrint);
    } else if (state->getFileName().empty()) {
        updateStatus("");
    }
}

void VM::VMModel::updateStatus(const std::string &message) {
    if (recording) {
        Model::updateStatus(message + " -- recording @" + recordingName + " --");
    } else {
        Model::updateStatus(message);
    }
}

bool VM::VMModel::isRecording() const {
    return recording;
}

const std::vector<int> &VM::VMModel::getInput() {
    signalMacroInfoDestruction();
    if (playing) {
        int c = macroInfos.back()->getLastCharacter();
        inputSimulator.push_back(c);
        return inputSimulator;
    }
    const std::vector<int> &seq = Model::getInput();
    if (recording) {
        recordingSequence.push_back(seq.back());
    }
    return seq;
}

void VM::VMModel::partlyEraseRecordingSequence(const std::vector<int> &seq) {
    if (recording) {
        for (int i = 0; i< seq.size(); ++i){
            if (!recordingSequence.empty()) {
                recordingSequence.pop_back();
            }
        }
    }
}

bool VM::VMModel::isPlaying() const {
    return playing;
}

void VM::VMModel::playMacro(const std::string &name) {
    if (!playing) {
        macroInfos.clear();
    }
    macroInfos.push_back(std::make_unique<MacroInfo>(*this, name));
    if (macroInfos.back()->isValid()) {
        if (!playing) lastPlayedMacro = name;
        playing = true;
    } else {
        macroInfos.pop_back();
    }
}

void VM::VMModel::signalMacroInfoDestruction() {
    if (!playing) return;
    if (!macroInfos.empty() && macroInfos.back()->isEmpty()) {
        macroInfos.pop_back();
    }
    if (macroInfos.empty()) {
        playing = false;
        inputSimulator.clear();
    }
}

size_t VM::VMModel::getCurrentState() const {
    return currentState;
}

const std::string &VM::VMModel::getLastPlayedMacro() const {
    return lastPlayedMacro;
}

