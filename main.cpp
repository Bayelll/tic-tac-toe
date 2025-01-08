#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

bool flag = true;

class GameBoard
{
private:
    const int SIZE{3};
    char** board;

public:
    GameBoard()
    {
        board = new char*[SIZE];

        for(int i = 0; i < SIZE; i++)
        {
            board[i] = new char[SIZE];
        }

        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                board[i][j] = '.';
            }
        }
    }

    void displayBoard() const 
    {
        cout << "  " << "1" << " " << "2" << " " << "3" << endl;
        for(int i = 0; i < SIZE; i++)
        {
            cout << to_string(i + 1) << " ";
            for(int j = 0; j < SIZE; j++)
            {
                cout <<  board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isValidMove(int row, int col)
    {
        return board[row-1][col-1] == '.' ? true : false; 
    }

    void makeMove(int row, int col, char symbol)
    {
        symbol = tolower(symbol);
        if(isValidMove(row, col))
        {
            board[row-1][col-1] = symbol;
            checkWin(board[row-1][col-1]);
            flag = true;
            return;
        }
        flag = false;
    }

    bool checkWin(char symbol)
    {
        int win{0};
        for(int i = 0; i < SIZE; i++)
        {
            win = 0;
            for(int j = 0; j < SIZE; j++)
            {
                if(board[i][j] == symbol)
                {
                    win++;
                }
            }
            if(win == 3) return true;
        }

        int win1{0};
        for(int j = 0; j < SIZE; j++)
        {
            win1 = 0;
            for(int i = 0; i < SIZE; i++)
            {
                if(board[i][j] == symbol)
                {
                    win1++;
                }
            }
            if(win1 == 3) return true;
        }

        int win2{0};
        for(int i = 0; i < SIZE; i++)
        {
            win2 = 0;
            for(int j = 0; j < SIZE; j++)
            {
                if(board[j][j] == symbol) win2++;
            }
            if(win2 == 3) return true;
        }

        int win3{0};
        for(int i = 0; i < SIZE; i++)
        {
            win3 = 0;
            for(int j = 0; j < SIZE; j++)
            {
                if(board[j][2-j] == symbol) win3++;
            }
            if(win3 == 3) return true;
        }

        return false;
    }

    bool isDraw()
    {
        int res{0};

        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                if(board[i][j] == '.') res++;
            }
        }

        if(res == 0) return true;

        return false;
    }

    ~GameBoard()
    {
        for(int i = 0; i < SIZE; i++)
        {
            delete[] board[i];
        }
        delete[] board;
    }
};

class CurrentPlayer 
{
public:
    virtual char getSymbol() const = 0;
    virtual string get_name() const = 0;
    virtual pair<int, int> getMove() = 0;
};
//
class Player : public CurrentPlayer
{
private:
    string name;
    char symbol;

public:
    Player(const string& name, char symbol) : name(name), symbol(tolower(symbol)) {}

    Player();

    pair<int, int> getMove()
    {
        int row, col;
        

        while (cin >> row >> col)
        {
            if(row >= 1 && row <= 3 && col >= 1 && col <= 3)
                break;
            else
                cout << "Не верный ход!" << endl;
        }
        
        

        pair<int, int> move = {row, col};

        return move;
    }

    char getSymbol() const  {return symbol; }
    string get_name() const  {return name; }
};

class ComputerEasy : public CurrentPlayer
{
private:
    string name = "EasyBot";
    char symbol;

public:
    ComputerEasy() = default;
    ComputerEasy(char s) : symbol(tolower(s)) {}


    pair<int, int> getMove()
    {
        int row, col;
       
        srand(time(NULL));

        row = rand() % 3 + 1;
        col = rand() % 3 + 1; 
       
        pair<int, int> move = {row, col};

        return move;
    }

    char getSymbol() const  {return symbol; }
    string get_name() const  {return name; }
};



/////////////////////////////////////////////////////////////

class ComputerHard : public CurrentPlayer
{
private:
    string name = "HardBot";
    char symbol;

public:
    ComputerHard() = default;
    ComputerHard(char s) : symbol(tolower(s)) {}

    pair<int, int> getMove()
    {
        int row, col;
       
        srand(time(NULL));

        row = rand() % 3 + 1;
        col = rand() % 3 + 1; 
       
        pair<int, int> move = {row, col};

        return move;
    }

    char getSymbol() const  {return symbol; }
    string get_name() const  {return name; }
};

class GameManagerBotHard
{
private:
    GameBoard board;
    Player p1;
    ComputerHard computer;
    CurrentPlayer* currentPlayer;

public:
    GameManagerBotHard(const Player& p1) : p1(p1), computer(p1.getSymbol() == 'x' ? 'o' : 'x'), board() {}

    void runGame()
    {
        cout << endl;
        board.displayBoard();

        pair<int, int> move;    
        int first{0}, second{0};

        currentPlayer = &p1;

        while(1)
        {
            if(flag)
            {
                cout << "Игрок " << currentPlayer->get_name() << " введите координаты хода" << endl;
            }

            if(currentPlayer == &p1)
            {
                move = currentPlayer->getMove();  
                first = move.first;
                second = move.second;

                board.makeMove(first, second, currentPlayer->getSymbol()); 
                cout << endl;
                cout << "Игрок " << currentPlayer->get_name() << " сделал ход в " << first << " " << second << endl;
                cout << endl;
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
                

                cout << endl;
                cout << "Игрок " << currentPlayer->get_name() << " сделал ход в " << first << " " << second << endl;
                cout << endl;
                board.displayBoard();

            }

            if(board.checkWin(currentPlayer->getSymbol()))
            {
                cout << "Поздравляем выиграл игрок " << currentPlayer->get_name() << " " << "(" << currentPlayer->getSymbol() << ")" << endl;
                ofstream fout("winners.csv", ios::app);  

                fout <<  currentPlayer->get_name() << " " << "(" << currentPlayer->getSymbol() << ")" << endl;       

                fout.close();

                
                if(promptRestart())
                {
                    string name_player;
                    char symbol_player;

                    cout << "Игрок, введите своё имя и вариант: ";
                    cin >> name_player >> symbol_player;
                    symbol_player = tolower(symbol_player);

                    Player player(name_player, symbol_player);

                    GameManagerBotHard Gb(player);
                    Gb.runGame();
                }

                break;
            }
            
            if(!flag)
            {
                cout << "Не верный ход" << endl;
                flag = true;
                switchPlayeer();
                continue;
            }

            if(board.isDraw())
            {
                cout << "Ничья" << endl;
                break;
            }

            switchPlayeer();
        }
    }


    void switchPlayeer()
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

    bool promptRestart()
    {
        char y;
        cout << "Хотите сыграть снова? (y/n): ";
        cin >> y;
        

        return y == 'y' ? true : false;
    }
};

/////////////////////////////////////////////////////////////

class GameManagerBot
{
private:
    GameBoard board;
    Player p1;
    ComputerEasy computer;
    CurrentPlayer* currentPlayer;

public:
    GameManagerBot(const Player& p1) : p1(p1), computer(p1.getSymbol() == 'x' ? 'o' : 'x'), board() {}


    void runGame()
    {
        cout << endl;
        board.displayBoard();

        pair<int, int> move;    
        int first{0}, second{0};

        currentPlayer = &p1;

        while(1)
        {
            if(flag)
            {
                cout << "Игрок " << currentPlayer->get_name() << " введите координаты хода" << endl;
            }

            if(currentPlayer == &p1)
            {
                move = currentPlayer->getMove();  
                first = move.first;
                second = move.second;

                board.makeMove(first, second, currentPlayer->getSymbol()); 
                cout << endl;
                cout << "Игрок " << currentPlayer->get_name() << " сделал ход в " << first << " " << second << endl;
                cout << endl;
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
                

                cout << endl;
                cout << "Игрок " << currentPlayer->get_name() << " сделал ход в " << first << " " << second << endl;
                cout << endl;
                board.displayBoard();

            }

            if(board.checkWin(currentPlayer->getSymbol()))
            {
                cout << "Поздравляем выиграл игрок " << currentPlayer->get_name() << " " << "(" << currentPlayer->getSymbol() << ")" << endl;
                ofstream fout("winners.csv", ios::app);  

                fout <<  currentPlayer->get_name() << " " << "(" << currentPlayer->getSymbol() << ")" << endl;       

                fout.close();

                
                if(promptRestart())
                {
                    string name_player;
                    char symbol_player;

                    cout << "Игрок, введите своё имя и вариант: ";
                    cin >> name_player >> symbol_player;
                    symbol_player = tolower(symbol_player);

                    Player player(name_player, symbol_player);

                    GameManagerBot Gb(player);
                    Gb.runGame();
                }

                break;
            }
            
            if(!flag)
            {
                cout << "Не верный ход" << endl;
                flag = true;
                switchPlayeer();
                continue;
            }

            if(board.isDraw())
            {
                cout << "Ничья" << endl;
                break;
            }

            switchPlayeer();
        }
    }


    void switchPlayeer()
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

    bool promptRestart()
    {
        char y;
        cout << "Хотите сыграть снова? (y/n): ";
        cin >> y;
        

        return y == 'y' ? true : false;
    }
};

 /////////////////////////////////////////////////////////////////

class GameManager
{
private:
    GameBoard board;
    Player player1;
    Player player2;
    Player* currentPlayer;

public:

    
    GameManager(const Player& p1, const Player& p2) : board(), player1(p1), player2(p2) {}

    void runGame()
    {
        cout << endl;
        board.displayBoard();

        pair<int, int> move;    
        int first{0}, second{0};
        currentPlayer = &player1;

        while (1)
        {

            if(flag)
            {
                cout << "Игрок " << currentPlayer->get_name() << " введите координаты хода" << endl;
            }
            
            if(!flag)
            {
                cout << "Не верный ход" << endl;
                flag = true;
                switchPlayeer();
                continue;
            }

            

            move = currentPlayer->getMove();  
            first = move.first;
            second = move.second;


            board.makeMove(first, second, currentPlayer->getSymbol()); 
            cout << endl;
            cout << "Игрок " << currentPlayer->get_name() << " сделал ход в " << first << " " << second << endl;
            cout << endl;
            board.displayBoard();

            if(board.checkWin(currentPlayer->getSymbol()))
            {
                cout << "Поздравляем выиграл игрок " << currentPlayer->get_name() << " " << "(" << currentPlayer->getSymbol() << ")" << endl;
                ofstream fout("winners.csv", ios::app);  

                fout <<  currentPlayer->get_name() << " " << "(" << currentPlayer->getSymbol() << ")" << endl;       

                fout.close();

                if(promptRestart())
                {
                    cout << endl;

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

                break;
            }

            if(board.isDraw())
            {
                cout << "Ничья" << endl;
                break;
            }

            switchPlayeer();

        }
    
    }

    void switchPlayeer()
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

    bool promptRestart()
    {
        char y;
        cout << "Хотите сыграть снова? (y/n): ";
        cin >> y;
        

        return y == 'y' ? true : false;
    }
};


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