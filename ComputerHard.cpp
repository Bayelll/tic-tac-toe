#include "ComputerHard.h"
#include <cstdlib>
#include <ctime>

ComputerHard::ComputerHard() = default;

ComputerHard::ComputerHard(char s) : symbol(std::tolower(s)) {}

std::pair<int, int> ComputerHard::getMove()
{
    int row, col;

    srand(time(NULL));

    row = rand() % 3 + 1;
    col = rand() % 3 + 1;

    return {row, col};
}

char ComputerHard::getSymbol() const
{
    return symbol;
}

std::string ComputerHard::get_name() const
{
    return name;
}
