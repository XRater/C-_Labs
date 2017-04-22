#include <iostream>
#include "initializer.h"


int main(int argc, char** argv) {    
    try {
        Initializer init(argc, argv);        
        init.run();
    }
    catch(HuffmanException& e)  {
        std::cout << e.what();        
    }
    return 0;
}
