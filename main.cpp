#include "./model/VMModel.h"

int main(int argc, char *argv[]) {
    VM::VMModel model{argc-1, argv};
    model.start();
    return 0;
}
