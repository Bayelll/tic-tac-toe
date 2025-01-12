#ifndef COMPUTERHARD_H
#define COMPUTERHARD_H

#include "CurrentPlayer.h"
#include <string>
#include <utility>

class ComputerHard : public CurrentPlayer
{
private:
    std::string name = "HardBot";
    char symbol;

public:
    ComputerHard();
    ComputerHard(char s);

    std::pair<int, int> getMove() override;
    char getSymbol() const override;
    std::string get_name() const override;
};

#endif // COMPUTERHARD_H
