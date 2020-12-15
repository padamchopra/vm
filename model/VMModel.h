#ifndef VM_VMMODEL_H
#define VM_VMMODEL_H

#include "Model.h"
#include "../mode/Mode.h"
#include "../utility/MacroInfo.h"

enum Modes {NORMAL_MODE = 0, INSERT_MODE = 1, EX_MODE = 2};
enum SpecialChars {CTRL_C = 3, ENTER = 10, BACKSPACE = 127, ESC = 27, RARROW = 261, UARROW = 259, LARROW = 260, DARROW= 258, CTRL_B = 2, CTRL_F =6, CTRL_D = 4, CTRL_G = 7, CTRL_R = 18, CTRL_U = 21};
namespace VM {
    class WindowState;

    class VMModel: public Model {
    private:
        bool enhanced;
        size_t currentState;
        size_t currentMode;
        std::vector<std::unique_ptr<WindowState>> states;
        std::vector<std::unique_ptr<Mode>> modes;
        std::vector<int> inputSimulator;
        std::string recordingName;
        std::vector<int> recordingSequence;
        std::string lastPlayedMacro;
        std::vector<std::unique_ptr<MacroInfo>> macroInfos;
        bool keepRunning;
        bool recording;
        bool playing;
        void initialise();
        void handleInteractions();
        void signalMacroInfoDestruction();
        void stop();

    public:
        VMModel(int fileCount, char *fileNames[]);
        void start();
        void setCurrentState(size_t currentState);
        size_t getCurrentState() const;
        WindowState *getActiveState() const;
        void changeMode(Modes m);
        void clearInputSequence();
        void updateStatus(const std::string &message) override;
        const std::vector<int> &getInput() override;
        Mode *getMode(Modes m);
        TerminalController *getController() const;
        void startRecordingSequence(const std::string &name);
        void stopRecordingSequence();
        void playMacro(const std::string &name);
        bool isRecording() const;
        bool isPlaying() const;
        const std::string &getLastPlayedMacro() const;
        void partlyEraseRecordingSequence(const std::vector<int> &seq);
        bool isEnhanced() const;
        void addState(const std::string &fileName);
        void removeActiveState();
    };
}


#endif //VM_VMMODEL_H
