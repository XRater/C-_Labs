#include "gameview.h"
#include <iostream>

void BoardView::showInfo() {
    std::cout << board_.get_width() << ' ' << board_.get_height() << '\n';
}


void BoardView::showBoard() {
    std::cout << '\n';        
    for (int i = 0; i < board_.get_height(); ++i) {
        for (int j = 0; j < board_.get_width(); ++j)
            std::cout << (char) board_.get_cell(i, j);
        std::cout << '\n';        
    }
}


void BoardView::startGame() {
    while (board_.gameStatus() == playing) {
        bool exit = doGameCycle();
        if (exit) 
            return; 
    }
    showResult();
}


bool BoardView::doGameCycle() {    
    if (!silence_)
        showBoard();
    int x, y;
    bool get_turn = true;
    cell_type turn = board_.get_turn();

    while (get_turn) {
        if (turn == X)
            std::cout << "X move: ";
        else
            std::cout << "O move: ";

        std::cin >> x >> y;
        if (x == -1 && y == -1)
            return 1;
        get_turn = board_.move(x, y, turn);
        if (get_turn)
            std::cout << "Bad move!\n";
    }
    return 0;
}


void BoardView::showResult() {
    showBoard();
    switch (board_.gameStatus()) {
        case playing:
            std::cout << "Error: unexpected game end.\n";
            return;
        case draw:
            std::cout << "Draw.\n";
            return;
        case XWin:
            std::cout << "X wins!\n";
            return;
        case OWin:
            std::cout << "O wins!\n";            
            return;
    }      
}


