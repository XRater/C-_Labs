#pragma once
#include "Test.h"
#include "gamemodel.h"


class BoardTest : public Test {
public:
    void testInit();

    void testCheckTurn();
    void testDoMoves();
    void testIncorrectTurn();
    void testStatusPlay();
    void testStatusWinD1();
    void testStatusWinD2();
    void testStatusWinV();
    void testStatusWinH();
    void testIsIn();
    void testIsEmpty();
    
           
    void runAllTests();
};

