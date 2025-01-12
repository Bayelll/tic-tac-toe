#include "Player.h"
#include <iostream>
#include <cctype>

Player::Player(const std::string& name, char symbol) : name(name), symbol(std::tolower(symbol)) {}

Player::Player() = default;  

std::pair<int, int> Player::getMove()
{
    int row, col;

    while (std::cin >> row >> col)
    {
        if (row >= 1 && row <= 3 && col >= 1 && col <= 3)
            break;
        else
            std::cout << "Неверный ход!" << std::endl;
    }

    return {row, col};
}

char Player::getSymbol() const
{
    return symbol;
}

std::string Player::get_name() const
{
    return name;
}
