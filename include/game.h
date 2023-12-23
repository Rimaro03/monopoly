#ifndef GAME_H
#define GAME_H

#include <string>

#include "table.h"
#include "human.h"
#include "bot.h"

class Game{
public:
    Game(const std::string& arg);
    void run();
private: 
    int gameType_;
    //Table table_;
    //Human human_;
    //Bot bot_[4];
};

#endif