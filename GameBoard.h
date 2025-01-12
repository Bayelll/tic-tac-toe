#ifndef GameBoard_H
#define GameBoard_H

#include <iostream>
#include <string>

using namespace std;

extern bool flag;

class GameBoard
{
private:
    const int SIZE{3};
    char** board;
    bool flag;

public:
    GameBoard();
    ~GameBoard();

    void displayBoard() const;
    bool isValidMove(int row, int col);
    void makeMove(int row, int col, char symbol);
    bool checkWin(char symbol);
    bool isDraw();
};

#endif
