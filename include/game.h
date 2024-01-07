//FILIPPO BATTISTI - 2066659

#ifndef GAME_H
#define GAME_H

#include "table.h"
#include "human.h"
#include "bot.h"
#include "output.h"

class Game{
public:
    // Non è possibile copiare o assegnare Game
    Game& operator=(const Game&) = delete;

    // Ritorna l'istanza di Game
    static Game& Get();

    // Inizializza il gioco
    static void Init(const std::string& arg);
    // Esegue un comando come "show"
    static void Show();
    // Logga in log.txt 
    static void UpdateLog(const std::string& message);
    // Logga in console
    static void Log(const std::string& message);
    // Esegue il gioco
    static void Run();
    // Ritorna le coordinate di una casella
    static std::string GetCoordinate(int position);
    // trasforma da posizione lineare a posizione x
    static int X(int position);
    // trasforma da posizione lineare a posizione y
    static int Y(int position);
    
    static bool Initialized();
private: 
    GameType gameType_; // tipo di gioco (pve, eve)
    Output output_; // output
    Table table_; // tabella di gioco
    Human human_; // giocatore umano
    Bot bots_[4]; // giocatori bot

    Game();

    void init_Internal(const std::string& arg);
    void show_Internal();
    void updateLog_Internal(const std::string& message);
    void log_Internal(const std::string& message);
    void run_Internal();

    void choosePlayersTurnOrder(std::array<Player*, PLAYERS_COUNT>& player_ptrs);
    void getWinner();
};

#endif