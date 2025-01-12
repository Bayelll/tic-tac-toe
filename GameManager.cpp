#include "GameManager.h"
#include <iostream>
#include <fstream>

GameManager::GameManager(const Player& p1, const Player& p2) : board(), player1(p1), player2(p2) {}

void GameManager::runGame()
{
    std::cout << std::endl;
    board.displayBoard();

    std::pair<int, int> move;    
    int first{0}, second{0};
    currentPlayer = &player1;

    while (1)
    {
        if(flag)
        {
            std::cout << "Игрок " << currentPlayer->get_name() << " введите координаты хода" << std::endl;
        }

        if(!flag)
        {
            std::cout << "Не верный ход" << std::endl;
            flag = true;
            switchPlayeer();
            continue;
        }

        move = currentPlayer->getMove();  
        first = move.first;
        second = move.second;

        board.makeMove(first, second, currentPlayer->getSymbol()); 
        std::cout << std::endl;
        std::cout << "Игрок " << currentPlayer->get_name() << " сделал ход в " << first << " " << second << std::endl;
        std::cout << std::endl;
        board.displayBoard();

        if(board.checkWin(currentPlayer->getSymbol()))
        {
            std::cout << "Поздравляем выиграл игрок " << currentPlayer->get_name() << " " << "(" << currentPlayer->getSymbol() << ")" << std::endl;
            std::ofstream fout("winners.csv", std::ios::app);  

            fout <<  currentPlayer->get_name() << " " << "(" << currentPlayer->getSymbol() << ")" << std::endl;       

            fout.close();

            if(promptRestart())
            {
                std::cout << std::endl;

                std::string name_player1;
                char symbol_player1;

                std::string name_player2;
                char symbol_player2;

                std::cout << "Игрок 1, введите своё имя и вариант: ";
                std::cin >> name_player1;

                while (std::cin >> symbol_player1)
                {
                    if(symbol_player1 == 'x' || symbol_player1 == 'X' || symbol_player1 == 'o' || symbol_player1 == 'O' ) break;
                    std::cout << "Не верный элемент (X\\0)" << std::endl;
                }

                std::cout << std::endl;

                std::cout << "Игрок 2, введите своё имя: ";
                std::cin >> name_player2;
                std::cout << std::endl;

                symbol_player2 = ((symbol_player1) == 'x' || (symbol_player1 == 'X')) ? 'o' : 'x';

                Player player1(name_player1, symbol_player1);
                Player player2(name_player2, symbol_player2);

                GameManager g(player1, player2);

                g.runGame();
            }

            break;
        }

        if(board.isDraw())
        {
            std::cout << "Ничья" << std::endl;
            break;
        }

        switchPlayeer();
    }
}

void GameManager::switchPlayeer()
{
    if(currentPlayer == &player1)
    {
        currentPlayer = &player2;
    }
    else 
    {
        currentPlayer = &player1;
    }
}

bool GameManager::promptRestart()
{
    char y;
    std::cout << "Хотите сыграть снова? (y/n): ";
    std::cin >> y;

    return y == 'y' ? true : false;
}
