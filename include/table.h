#ifndef TABLE_H
#define TABLE_H
#include <array>
#include "bot.h"
#include "human.h"
#include "box.h"

class Table
{
public:
    Table();
    ~Table();

    void turn();
    void players(Player *player1, Player *player2, Player *player3, Player *player4);

    std::array<Box*, 28> map();
    std::array<Player*, 4> players();

private:
    //usare gli array con il loro iteratore
    std::array<Box*, 28> map_;
    std::array<Player*, 4> players_;
};

#endif