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
    /** @brief Initialize the game. */
    static void Init(const std::string& arg);
    /**
    * @brief Execute a command.
    * @param command : The command to execute, it can be: "show", "show balances", "show list", "show table".
    */
    static void Command(const std::string& command);
    /**
    * @brief Updates the log.txt file.
    * @param message : The message to write in the log file.
    */
    static void UpdateLog(const std::string& message);
    /**
    * @brief Writes a message in the console. 
    * Same as std::cout << message << std::endl.
    */
    static void Log(const std::string& message);
    /** @brief Executes the main game loop. */
    static void Run();
    /** @brief Returns a string representing the coordinate of a position. */
    static std::string GetCoordinate(int position);
    /** @brief Returns the x of the position. */
    static int X(int position);
    /** @brief Returns the y of the position. */
    static int Y(int position);
    
    /** @brief Returns true if the game has been initialized. */
    static bool Initialized();
private: 
    /** @brief The game type*/
    GameType gameType_;
    /** @brief The output log manager. */
    Output output_;
    /** @brief The game board. */
    Table table_; 
    /** @brief The human player. */
    Human human_;
    /** @brief The bot players. */
    std::array<Bot, PLAYERS_COUNT> bots_;

    Game();

    /* @brief Returns the instance of game. **/
    static Game& Get();

    /* INTERNAL METHODS */

    void init_Internal(const std::string& arg);
    void updateLog_Internal(const std::string& message);
    void log_Internal(const std::string& message);
    void run_Internal();
    void command_Internal(const std::string& command);

    /** @brief Choose the player order and initialize the board. */
    void choosePlayersTurnOrder(std::array<Player*, PLAYERS_COUNT>& player_ptrs);
    /** @brief Determine the winner and prints them. */
    void printWinner();
};

#endif