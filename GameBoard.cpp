#include "GameBoard.h"

bool flag = true;

GameBoard::GameBoard()
{
    board = new char*[SIZE];

    for(int i = 0; i < SIZE; i++)
    {
        board[i] = new char[SIZE];
    }

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            board[i][j] = '.';
        }
    }
}

void GameBoard::displayBoard() const 
{
    cout << "  " << "1" << " " << "2" << " " << "3" << endl;
    for(int i = 0; i < SIZE; i++)
    {
        cout << to_string(i + 1) << " ";
        for(int j = 0; j < SIZE; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool GameBoard::isValidMove(int row, int col)
{
    return board[row-1][col-1] == '.' ? true : false; 
}

void GameBoard::makeMove(int row, int col, char symbol)
{
    symbol = tolower(symbol);
    if(isValidMove(row, col))
    {
        board[row-1][col-1] = symbol;
        checkWin(board[row-1][col-1]);
        flag = true;
        return;
    }
    flag = false;
}

bool GameBoard::checkWin(char symbol)
{
    int win{0};
    for(int i = 0; i < SIZE; i++)
    {
        win = 0;
        for(int j = 0; j < SIZE; j++)
        {
            if(board[i][j] == symbol)
            {
                win++;
            }
        }
        if(win == 3) return true;
    }

    int win1{0};
    for(int j = 0; j < SIZE; j++)
    {
        win1 = 0;
        for(int i = 0; i < SIZE; i++)
        {
            if(board[i][j] == symbol)
            {
                win1++;
            }
        }
        if(win1 == 3) return true;
    }

    int win2{0};
    for(int i = 0; i < SIZE; i++)
    {
        win2 = 0;
        for(int j = 0; j < SIZE; j++)
        {
            if(board[j][j] == symbol) win2++;
        }
        if(win2 == 3) return true;
    }

    int win3{0};
    for(int i = 0; i < SIZE; i++)
    {
        win3 = 0;
        for(int j = 0; j < SIZE; j++)
        {
            if(board[j][2-j] == symbol) win3++;
        }
        if(win3 == 3) return true;
    }

    return false;
}

bool GameBoard::isDraw()
{
    int res{0};

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            if(board[i][j] == '.') res++;
        }
    }

    if(res == 0) return true;

    return false;
}

GameBoard::~GameBoard()
{
    for(int i = 0; i < SIZE; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}
