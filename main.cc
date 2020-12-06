#include <iostream>
#include "vmmodel.h"

int main(int argc, char *argv[]) {
    //argc will at least be 1 (program name)
    //so argc - 1 will at least be 0
    //it is safe to cast it to size_t
    size_t fileCount = static_cast<size_t>(argc-1);
    VM::VMModel model{fileCount, argv};
    model.start();
}
