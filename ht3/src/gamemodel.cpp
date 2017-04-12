#include "gamemodel.h"
#include "iostream"

Board::Board(int w, int h) : width_(w), height_(h), turn_(O) {
    cells_ = new cell_type* [h];
    for (int i = 0; i < h; ++i) { 
        cells_[i] = new cell_type[w];
        for (int j = 0; j < w; ++j)
            cells_[i][j] = empty;
    }
}


Board::~Board() {
    for (int i = 0; i != height_; ++i) {
        delete [] cells_[i];
    }
    delete [] cells_;
}


bool Board::move(int x, int y, cell_type turn) {
    if (!can_move(x, y))
        return 1;

    cells_[x][y] = turn;    
    change_turn();

    return 0;
}


bool Board::isinBoard(int x, int y) {
    if (x < 0 || x >= width_)
        return 0;
    if (y < 0 || y >= height_)
        return 0;
 
    return 1;
}


game_status Board::gameStatus() {
    
    bool isfull = true;
    for (int i = 0; i < width_; ++i)
        for (int j = 0; j < height_; ++j) {    
        
            if (isEmpty(i, j)) {
                isfull = false;
                continue;
            }
            
            if (checkLine(i, j)) {
                if (cells_[i][j] == X)
                    return XWin;
                else
                    return OWin;
            }                
            
        }
    
    if (isfull)
        return draw;
    
    return playing;
}


bool Board::checkLine(int x, int y) {
    cell_type cell = cells_[x][y];
    for (int dx = 0; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0)
                continue;

            bool notLine = false;
            for (int k = 1; k < 5; k++) {
                if (!isinBoard(x + k * dx, y + k * dy)) { 
                    notLine = true;
                    continue;
                }
                
                if (cell != cells_[x + k * dx][y + k * dy]) {
                    notLine = true; 
                    continue;
                }
            }

            if (!notLine)
                return true;
        }
    return false;
}


bool Board::isEmpty(int x, int y) {
    return (cells_[x][y] == empty);    
}

void Board::change_turn() {
    if (turn_ == X)
        turn_ = O;
    else if (turn_ == O)
        turn_ = X;
}
