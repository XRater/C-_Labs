#include "gamemodel.h"
#include "iostream"

Board::Board(int w, int h) : width_(w), height_(h) {
  cells_ = new Cell* [h];
  for (int i = 0; i != h; ++i) {
    cells_[i] = new Cell[w];
  }
}


Board::~Board() {
    for (int i = 0; i != height_; ++i) {
        delete [] cells_[i];
    }
    delete [] cells_;
}


bool Board::move(int x, int y) {
    if (!isinBoard(x, y))
        return 1;
    if (!isEmpty(x, y))
        return 1;
    
    if (turn_ == 0)
        cells_[x][y].set_value(X);
    if (turn_ == 1)
        cells_[x][y].set_value(O);
    turn_ ^= 1;

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
    
    bool isfull = 1;
    for (int i = 0; i < width_; ++i)
        for (int j = 0; j < height_; ++j) {    
        
            if (isEmpty(i, j)) {
                isfull = 0;
                continue;
            }
            
            if (checkLine(i, j)) {
                if (cells_[i][j].get_value() == X)
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
    cell_type cell = cells_[x][y].get_value();
    for (int dx = 0; dx <= 1; ++dx)
        for (int dy = 0; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0)
                continue;

            int flag = 0;
            for (int k = 1; k < 5; k++) {
                if (!isinBoard(x + k * dx, y + k * dy)) { 
                    flag = 1;
                    continue;
                }
                
                if (cell != cells_[x + k * dx][y + k * dy].get_value()) {
                    flag = 1; 
                    continue;
                }
            }

            if (flag == 0)
                return true;
        }
    return false;
}


bool Board::isEmpty(int x, int y) {
    return (cells_[x][y].get_value() == empty);    
}

