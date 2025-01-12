#ifndef PLAYER_H
#define PLAYER_H

#include "CurrentPlayer.h"
#include <string>
#include <utility>

class Player : public CurrentPlayer
{
private:
    std::string name;
    char symbol;

public:
    Player(const std::string& name, char symbol);
    Player();  // Конструктор по умолчанию

    std::pair<int, int> getMove() override;
    char getSymbol() const override;
    std::string get_name() const override;
};

#endif // PLAYER_H
