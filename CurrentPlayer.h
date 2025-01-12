#ifndef CURRENTPLAYER_H
#define CURRENTPLAYER_H

#include <string>
#include <utility>

using namespace std;

class CurrentPlayer
{
public:
    virtual char getSymbol() const = 0;
    virtual string get_name() const = 0;
    virtual pair<int, int> getMove() = 0;

    virtual ~CurrentPlayer() = default;
};

#endif 
