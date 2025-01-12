#ifndef COMPUTEREASY_H
#define COMPUTEREASY_H

#include "CurrentPlayer.h"
#include <string>
#include <utility>

class ComputerEasy : public CurrentPlayer
{
private:
    std::string name = "EasyBot";
    char symbol;

public:
    ComputerEasy();
    ComputerEasy(char s);

    std::pair<int, int> getMove() override;
    char getSymbol() const override;
    std::string get_name() const override;
};

#endif 
