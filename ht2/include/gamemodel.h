#pragma once

enum cell_type {empty = '.', X = 'X', O = 'O'};
enum game_status {playing = 0, draw = 1, XWin = 2, OWin = 3};  
  
class Board {
public:
    Board(int width = 10, int height = 10);
    ~Board();
    
    int get_width() {return width_;}
    int get_height() {return height_;}
    int get_turn() {return turn_;}
    cell_type get_cell(int i, int j) {return cells_[i][j].get_value();}
    
    bool move(int x, int y);
    bool isinBoard(int x, int y);
    bool isEmpty(int x, int y);
    
    game_status gameStatus();
    bool checkLine(int x, int y);
    
private:
    class Cell {
    public:
        Cell() : value_(empty) {};
    
        cell_type get_value() {return value_;}
        void set_value(cell_type type) {value_ = type;}
    private:
        cell_type value_;    
    };

    int width_;
    int height_;
    Cell** cells_;    
        
    bool turn_ = 1;
};

