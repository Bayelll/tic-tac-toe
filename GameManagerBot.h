#ifndef GAMEMANAGERBOT_H
#define GAMEMANAGERBOT_H

#include "GameBoard.h"
#include "Player.h"
#include "ComputerEasy.h"
#include <fstream>
#include <string>

class GameManagerBot
{
private:
    GameBoard board;
    Player p1;
    ComputerEasy computer;
    CurrentPlayer* currentPlayer;

public:
    GameManagerBot(const Player& p1);

    void runGame();
    void switchPlayeer();
    bool promptRestart();
};

#endif 
