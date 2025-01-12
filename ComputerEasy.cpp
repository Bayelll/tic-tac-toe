#include "ComputerEasy.h"
#include <cstdlib>
#include <ctime>

ComputerEasy::ComputerEasy() = default;

ComputerEasy::ComputerEasy(char s) : symbol(std::tolower(s)) {}

std::pair<int, int> ComputerEasy::getMove()
{
    int row, col;

    srand(time(NULL));

    row = rand() % 3 + 1;
    col = rand() % 3 + 1;

    return {row, col};
}

char ComputerEasy::getSymbol() const
{
    return symbol;
}

std::string ComputerEasy::get_name() const
{
    return name;
}
