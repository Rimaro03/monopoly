/**
 * @author: Leonardo Ongaro - 2074985
 */

#ifndef TABLE_H
#define TABLE_H

#include <array>

#include "rules.h"
#include "bot.h"
#include "human.h"
#include "box.h"

class Table
{
private:
    std::array<Box *, BOX_COUNT> map_;
    std::array<Player *, PLAYERS_COUNT> players_;

public:
    /* Setters and Getters */
    std::array<Box *, BOX_COUNT> &map();
    std::array<Player *, PLAYERS_COUNT> &players();
    void players(std::array<Player *, PLAYERS_COUNT> &players);

    /**
     * @brief Construct a new Table object: generate and insert randomly all the boxes
     */
    Table();
    /**
     * @brief Destruct the Table object: deallocates all the Boxes
     */
    ~Table();

    /**
     * @brief Executes the `turn` method for each Player in the game
     */
    void turn();

    /**
     * @brief Check if wether there is a winner before playing the next round
     */
    bool hasWinner() const;
};

#endif