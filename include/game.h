//FILIPPO BATTISTI - 2066659

#ifndef GAME_H
#define GAME_H

#include <array>

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
    static void Show();    // DA ELIMINARE
    // Esegue un comando come "show", "show table", "show list", "show balances" e ritorna true se il comando è stato eseguito
    static bool Command(const std::string& command);
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
    std::array<Bot, PLAYERS_COUNT> bots_; // giocatori bot

    Game();

    void init_Internal(const std::string& arg);
    void show_Internal();
    void updateLog_Internal(const std::string& message);
    void log_Internal(const std::string& message);
    void run_Internal();
    
    bool command_Internal(const std::string& command);

    void choosePlayersTurnOrder(std::array<Player*, PLAYERS_COUNT>& player_ptrs);
    void getWinner();
};

#endif