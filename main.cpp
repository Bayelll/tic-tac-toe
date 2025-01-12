#include <vector>

#include "GameBoard.h"
#include "CurrentPlayer.h"
#include "Player.h"
#include "ComputerEasy.h"
#include "ComputerHard.h"
#include "GameManagerBotHard.h"
#include "GameManagerBot.h"
#include "GameManager.h"

// compile command - g++ main.cpp GameBoard.cpp Player.cpp ComputerEasy.cpp ComputerHard.cpp GameManagerBotHard.cpp GameManagerBot.cpp GameManager.cpp  -o main

int main()
{

    cout << endl << "Добро пожаловать в \"Крестики-нолики\"!" << endl;
    cout << endl;

    cout << "1. " << "Показать результаты последних 5 игр" << endl;
    cout << "2. " << "Начать игру с другом" << endl;
    cout << "3. " << "Начать игру с компьютером" << endl;

    cout << endl;
    int choice;
    cin >> choice;
    cout << endl;

    if(choice == 1)
    {
        FILE* fout = fopen("winners.csv", "r");

        vector <string> winners;

        if(fout != NULL)
        {
            char line[100];
            while (fgets(line, sizeof(line), fout))
            {
                winners.push_back(line);
            }
        }

        int end = winners.size() - 1;

        int start = max(0, end - 4);

        for (int i = start; i <= end; i++) {
            cout << winners[i];
        }

        cout << endl;
    }

    if(choice == 2)
    {
        string name_player1;
        char symbol_player1;

        string name_player2;
        char symbol_player2;

        cout << "Игрок 1, введите своё имя и вариант: ";
        cin >> name_player1;

        while (cin >> symbol_player1)
        {
            if(symbol_player1 == 'x' || symbol_player1 == 'X' || symbol_player1 == 'o' || symbol_player1 == 'O' ) break;
            cout << "Не верный элемент (X\\0)" << endl;
        }
    
        cout << endl;

        cout << "Игрок 2, введите своё имя: ";
        cin >> name_player2;
        cout << endl;
    
        symbol_player2 = ((symbol_player1) == 'x' || (symbol_player1 == 'X')) ? 'o' : 'x';

        Player player1(name_player1, symbol_player1);
        Player player2(name_player2, symbol_player2);

        GameManager g(player1, player2);

        g.runGame();
    }

    if(choice == 3)
    {
        int choice;
        cout << endl;

        cout << "Выберите сложность" << endl;
        cout << "1 - Легкий" << endl;
        cout << "2 - Сложный" << endl;
        cout << endl;
        cin >> choice;

        if(choice < 1 || choice > 2)
        {
            cout << "Ошибка выбора" << endl;
        }

        if(choice == 1)
        {
            string name_player;
            char symbol_player;

            cout << endl;
            cout << "Игрок, введите своё имя и вариант: ";
            cin >> name_player;

            while (cin >> symbol_player)
            {
                if(symbol_player == 'x' || symbol_player == 'X' || symbol_player == 'o' || symbol_player == 'O' ) break;
                cout << "Не верный элемент (X\\0)" << endl;
            }
            symbol_player = tolower(symbol_player);

            Player player(name_player, symbol_player);

            GameManagerBot Gb(player);
            Gb.runGame();
        }

        if(choice == 2)
        {
            string name_player;
            char symbol_player;

            cout << endl;
            cout << "Игрок, введите своё имя и вариант: ";
            cin >> name_player;

            while (cin >> symbol_player)
            {
                if(symbol_player == 'x' || symbol_player == 'X' || symbol_player == 'o' || symbol_player == 'O' ) break;
                cout << "Не верный элемент (X\\0)" << endl;
            }
            symbol_player = tolower(symbol_player);

            Player player(name_player, symbol_player);

            GameManagerBotHard Gb(player);
            Gb.runGame();
        }
    }

    if(choice < 1 || choice > 3)
    {
        cout << "Некрректный ввод" << endl;
    }

    return 0;
}