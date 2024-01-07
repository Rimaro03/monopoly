#ifndef TABLE_H
#define TABLE_H

#include <array>

#include "rules.h"
#include "bot.h"
#include "human.h"
#include "box.h"

class Table
{
public:
    Table();
    ~Table();

    void turn();
    void players(std::array<Player*, PLAYERS_COUNT>& players);
    
    bool hasWinner() const;

    std::array<Box*, BOX_COUNT>& map();
    std::array<Player*, PLAYERS_COUNT>& players();

private:
    std::array<Box*, BOX_COUNT> map_;
    std::array<Player*, PLAYERS_COUNT> players_;
};

#endif