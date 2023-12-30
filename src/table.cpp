#include <iostream>
#include <algorithm>
#include <random>
#include "table.h"
#include "sideBox.h"
#include "lateralBox.h"

Table::Table() : players_{nullptr, nullptr, nullptr, nullptr}
{
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
        if (count < ECONOMIC_BOXES_COUNT)
        {
            casella = new LateralBox(indici[i], BoxType::economic);
        }
        else if (count < ECONOMIC_BOXES_COUNT + STANDARD_BOXES_COUNT)
        {
            casella = new LateralBox(indici[i], BoxType::standard);
        }
        else
        {
            casella = new LateralBox(indici[i], BoxType::luxury);
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

void Table::players(Player *players[PLAYERS_COUNT])
{
    for (int i = 0; i < PLAYERS_COUNT; i++)
    {
        players_[i] = players[i];
    }
}

void Table::turn()
{
    for (Player *p : players_)
    {
        if (!p)
        {
            throw std::runtime_error("Player is null!");
        }
        p->turn(this);
    }
}

std::array<Box *, BOX_COUNT> &Table::map()
{
    return map_;
}

std::array<Player *, PLAYERS_COUNT> &Table::players()
{
    return players_;
}

bool Table::hasWinner() const
{
    int counter = 0;
    for (Player *p : players_)
    {
        if (p->balance() >= 0)
        {
            counter++;
        }
    }
    return counter == 1;
}