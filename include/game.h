#ifndef GAME_H
#define GAME_H

#include "table.h"
#include "human.h"
#include "bot.h"
#include "output.h"

class Game{
public:
    Game& operator=(const Game&) = delete;

    // Ritorna l'istanza di Game
    static Game& Get();

    // Inizializza il gioco
    static void Init(const std::string& arg);
    // Esegue un comando come "show"
    static void Command(const std::string& command);
    // Logga in log.txt 
    static void UpdateLog(const std::string& message);
    // Logga in console
    static void Log(const std::string& message);
    // Esegue il gioco
    static void Run();
    // Ritorna le coordinate di una casella
    static std::string GetCoordinate(int position);
    static int X(int position);
    static int Y(int position);
    
    static bool Initialized();
private: 
    int gameType_;
    Output output_;
    Table table_;
    Human human_;
    Bot bot_[4];

    Game();

    void init_Internal(const std::string& arg);
    void command_Internal(const std::string& command);
    void updateLog_Internal(const std::string& message);
    void log_Internal(const std::string& message);
    void run_Internal();
};

#endif