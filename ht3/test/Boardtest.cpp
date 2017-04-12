#include "Boardtest.h"

#define DO_CHECK(EXPR) Test::check(EXPR, __FUNCTION__, __FILE__, __LINE__); 


void BoardTest::runAllTests() {
    testInit();          //2
    testDoMoves();       //2
    testIncorrectTurn(); //8
    testStatusPlay();    //5
    testStatusWinD1();   //1
    testStatusWinD2();   //1
    testStatusWinH();    //1
    testStatusWinV();    //1
    testIsIn();          //7
    testIsEmpty();       //3
}


void BoardTest::testInit() {
    Board m1;
    DO_CHECK(m1.get_width() == 10 && m1.get_height() == 10);
    Board m2(3, 4);
    DO_CHECK(m2.get_width() == 3 && m2.get_height() == 4);
}


void BoardTest::testDoMoves() {
    Board m;
    DO_CHECK(m.get_cell(1, 4) == empty && m.get_cell(3, 5) == empty);
    m.move(2, 4, O);
    m.move(5, 6, X);
    DO_CHECK(m.get_cell(2, 4) == O && m.get_cell(5, 6) == X && m.get_cell(6, 8) == empty);    
}


void BoardTest::testIncorrectTurn() {
    Board m;
    DO_CHECK(m.get_turn() == O);
    m.move(3, 5, O);
    DO_CHECK(m.get_turn() == X);
    m.move(3, 5, X);
    DO_CHECK(m.get_turn() == X);
    m.move(0, 10, X);
    DO_CHECK(m.get_turn() == X);
    m.move(6, 2, X);
    DO_CHECK(m.get_turn() == O);
    m.move(6, 2, O);
    DO_CHECK(m.get_turn() == O);
    m.move(5, 5, O);
    DO_CHECK(m.get_turn() == X);
    DO_CHECK(m.get_cell(3, 5) == O && m.get_cell(6, 2) == X
             && m.get_cell(5, 5) == O && m.get_cell(9, 5) == empty);    
}


void BoardTest::testStatusPlay() {
    Board m(2, 2);
    DO_CHECK(m.gameStatus() == playing);
    m.move(0, 0, O);
    DO_CHECK(m.gameStatus() == playing);
    m.move(0, 1, X);
    DO_CHECK(m.gameStatus() == playing);
    m.move(1, 0, O);
    DO_CHECK(m.gameStatus() == playing);
    m.move(1, 1, X);
    DO_CHECK(m.gameStatus() == draw);
}

void BoardTest::testStatusWinD1() {
    Board m;
    m.move(2, 3, O);
    m.move(5, 5, X);
    m.move(3, 4, O);
    m.move(7, 7, X);
    m.move(5, 6, O);
    m.move(9, 9, X);
    m.move(1, 2, O);
    m.move(1, 1, X);
    m.move(4, 5, O);
    DO_CHECK(m.gameStatus() == OWin);
}

void BoardTest::testStatusWinD2() {
    Board m;
    m.move(6, 2, O);
    m.move(4, 5, X);
    m.move(1, 1, O);
    m.move(3, 4, X);
    m.move(5, 6, O);
    m.move(2, 3, X);
    m.move(0, 2, O);
    m.move(1, 2, X);
    m.move(9, 8, O);
    m.move(0, 1, X);
    DO_CHECK(m.gameStatus() == XWin);
}

void BoardTest::testStatusWinV() {
    Board m;
    m.move(2, 3, O);
    m.move(5, 5, X);
    m.move(2, 7, O);
    m.move(7, 7, X);
    m.move(2, 5, O);
    m.move(9, 9, X);
    m.move(2, 4, O);
    m.move(1, 1, X);
    m.move(2, 6, O);
    DO_CHECK(m.gameStatus() == OWin);
}

void BoardTest::testStatusWinH() {
    Board m;
    m.move(9, 6, O);
    m.move(1, 5, X);
    m.move(9, 5, O);
    m.move(1, 2, X);
    m.move(9, 2, O);
    m.move(7, 9, X);
    m.move(9, 4, O);
    m.move(4, 1, X);
    m.move(9, 3, O);
    DO_CHECK(m.gameStatus() == OWin);
}


void BoardTest::testIsIn() {
    Board m1;
    DO_CHECK(m1.isinBoard(4, 5) == true);    
    DO_CHECK(m1.isinBoard(-1, 1) == false);    
    DO_CHECK(m1.isinBoard(10, 3) == false);    
    DO_CHECK(m1.isinBoard(0, 0) == true);    
    Board m2(3, 4);
    DO_CHECK(m2.isinBoard(3, 2) == false);    
    DO_CHECK(m2.isinBoard(2, 3) == true);    
    DO_CHECK(m2.isinBoard(3, 3) == false);    
}


void BoardTest::testIsEmpty() {
    Board m;
    DO_CHECK(m.isEmpty(3, 7) == true);
    m.move(2, 4, X);
    DO_CHECK(m.isEmpty(3, 9) == true);
    DO_CHECK(m.isEmpty(2, 4) == false);    
}


