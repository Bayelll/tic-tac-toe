#ifndef GAMEMANAGERBOTHARD_H
#define GAMEMANAGERBOTHARD_H

#include "GameBoard.h"
#include "Player.h"
#include "ComputerHard.h"
#include <fstream>
#include <string>

class GameManagerBotHard
{
private:
    GameBoard board;
    Player p1;
    ComputerHard computer;
    CurrentPlayer* currentPlayer;

public:
    GameManagerBotHard(const Player& p1);

    void runGame();
    void switchPlayeer();
    bool promptRestart();
};

#endif // GAMEMANAGERBOTHARD_H
