#pragma once
#include "gamemodel.h"

class BoardView {
public:
    BoardView(Board& brd, bool silence = 0)
         : board_(brd), silence_(silence) {};
    
    void showInfo();
    void showBoard();
    
    void startGame();
    bool doGameCycle();    
    void showResult();
    
private:
    Board& board_;
    bool silence_;
};
