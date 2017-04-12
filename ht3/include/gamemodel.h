#pragma once

enum cell_type {empty = '.', X = 'X', O = 'O'};
enum game_status {playing, draw, XWin, OWin};
  
class Board {
public:
    Board(int width = 10, int height = 10);
    ~Board();
    
    int get_width() {return width_;}
    int get_height() {return height_;}
    cell_type get_turn() {return turn_;}
    cell_type get_cell(int i, int j) {return cells_[i][j];}
    
    bool move(int x, int y, cell_type turn);
    bool can_move(int x, int y) {return isinBoard(x, y) & isEmpty(x, y);}
    bool isinBoard(int x, int y);
    bool isEmpty(int x, int y);
    
    game_status gameStatus();
    bool checkLine(int x, int y);
    
private:

    int width_;
    int height_;
    cell_type** cells_;    
        
    cell_type turn_;
    void change_turn();
};

