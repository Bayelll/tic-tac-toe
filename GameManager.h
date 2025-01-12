#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "GameBoard.h"
#include "Player.h"
#include <fstream>
#include <string>

class GameManager
{
private:
    GameBoard board;
    Player player1;
    Player player2;
    Player* currentPlayer;

public:
    GameManager(const Player& p1, const Player& p2);

    void runGame();
    void switchPlayeer();
    bool promptRestart();
};

#endif 
