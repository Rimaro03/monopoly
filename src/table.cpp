#include <iostream>
#include <algorithm>
#include <random>
#include "table.h"
#include "sideBox.h"
#include "lateralBox.h"

Table::Table()
{
    int ecoCount = 8;
    int standardCount = 10;
    int luxCount = 6;

    // generazione indici
    int indici[24]; //{0:1, 1:2, 2:3, 3:4, 4:5, 5:6, 6:8, 7:9, 8:10...}
    int j = 0;
    for (size_t i = 0; i < 24; i++)
    {
        if (j % 7 == 0)
        {
            j++;
        }
        indici[i] = j;
        j++;
    }

    // randomizzazione indici con shuffle()
    std::shuffle(indici, indici + 24, std::default_random_engine(time(NULL)));

    int count = 0;
    for (unsigned int i = 0; i < 24; i++)
    {
        Box *casella;
        if (count < 8)
        {
            casella = new LateralBox(indici[i], BoxType::economic, 6, 3, 3, 2, 4);
        }
        else if (count < 10)
        {
            casella = new LateralBox(indici[i], BoxType::standard, 10, 5, 5, 4, 8);
        }
        else
        {
            casella = new LateralBox(indici[i], BoxType::luxury, 20, 10, 10, 7, 14);
        }

        map_[indici[i]] = casella;
        count++;
    }

    map_[0] = new SideBox(0, true);
    map_[7] = new SideBox(7, false);
    map_[14] = new SideBox(14, false);
    map_[21] = new SideBox(21, false);
}

Table::~Table()
{
    for (Box *b : map_)
        delete[] b;
}

void Table::players(Player *player1, Player *player2, Player *player3, Player *player4)
{
    players_[0] = player1;
    players_[1] = player2;
    players_[2] = player3;
    players_[3] = player4;
}

void Table::turn()
{
    for (Player *p : players_)
        p->turn(this);
}

std::array<Box *, 28> Table::map()
{
    return map_;
}

std::array<Player *, 4> Table::players()
{
    return players_;
}