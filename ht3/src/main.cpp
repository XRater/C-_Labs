#include <cstring>
#include <cstdio>
#include "gameview.h"


int main(int argc, char** argv) {    
    bool silence = 0; 
    if (argc > 1)
        if (strcmp(argv[1], "silent") == 0)
            silence = 1;    
    
    Board brd;
    BoardView text_view(brd, silence);
    text_view.startGame();
    return 0;
}
