#include "GameManagerBot.h"
#include <iostream>
#include <fstream>

GameManagerBot::GameManagerBot(const Player& p1) : p1(p1), computer(p1.getSymbol() == 'x' ? 'o' : 'x'), board() {}

void GameManagerBot::runGame()
{
    std::cout << std::endl;
    board.displayBoard();

    std::pair<int, int> move;    
    int first{0}, second{0};

    currentPlayer = &p1;

    while(1)
    {
        if(flag)
        {
            std::cout << "Игрок " << currentPlayer->get_name() << " введите координаты хода" << std::endl;
        }

        if(currentPlayer == &p1)
        {
            move = currentPlayer->getMove();  
            first = move.first;
            second = move.second;

            board.makeMove(first, second, currentPlayer->getSymbol()); 
            std::cout << std::endl;
            std::cout << "Игрок " << currentPlayer->get_name() << " сделал ход в " << first << " " << second << std::endl;
            std::cout << std::endl;
            board.displayBoard();
        }
        else 
        {
            move = currentPlayer->getMove();
            first = move.first;
            second = move.second;

            board.makeMove(first, second, currentPlayer->getSymbol()); 

            while (flag == false)
            {
                move = currentPlayer->getMove();
                board.makeMove(first, second, currentPlayer->getSymbol()); 
                first = move.first;
                second = move.second;
            }

            std::cout << std::endl;
            std::cout << "Игрок " << currentPlayer->get_name() << " сделал ход в " << first << " " << second << std::endl;
            std::cout << std::endl;
            board.displayBoard();
        }

        if(board.checkWin(currentPlayer->getSymbol()))
        {
            std::cout << "Поздравляем выиграл игрок " << currentPlayer->get_name() << " " << "(" << currentPlayer->getSymbol() << ")" << std::endl;
            std::ofstream fout("winners.csv", std::ios::app);  

            fout <<  currentPlayer->get_name() << " " << "(" << currentPlayer->getSymbol() << ")" << std::endl;       

            fout.close();

            if(promptRestart())
            {
                std::string name_player;
                char symbol_player;

                std::cout << "Игрок, введите своё имя и вариант: ";
                std::cin >> name_player >> symbol_player;
                symbol_player = std::tolower(symbol_player);

                Player player(name_player, symbol_player);

                GameManagerBot Gb(player);
                Gb.runGame();
            }

            break;
        }
        
        if(!flag)
        {
            std::cout << "Не верный ход" << std::endl;
            flag = true;
            switchPlayeer();
            continue;
        }

        if(board.isDraw())
        {
            std::cout << "Ничья" << std::endl;
            break;
        }

        switchPlayeer();
    }
}

void GameManagerBot::switchPlayeer()
{
    if(currentPlayer == &p1)
    {
        currentPlayer = &computer;
    }
    else 
    {
        currentPlayer = &p1;
    }
}

bool GameManagerBot::promptRestart()
{
    char y;
    std::cout << "Хотите сыграть снова? (y/n): ";
    std::cin >> y;

    return y == 'y' ? true : false;
}
