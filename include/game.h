#ifndef GAME_H
#define GAME_H

#include <string>

#include "table.h"
#include "human.h"
#include "bot.h"
#include "output.h"

class Game{
public:
    Game& operator=(const Game&) = delete;

    static Game& Get();
    static void Init(const std::string& arg);
    static void Run();
private: 
    int gameType_;
    Output output_;
    //Table table_;
    //Human human_;
    //Bot bot_[4];

    Game();
    void init_Internal(const std::string& arg);
    void run_Internal();
};

#endif