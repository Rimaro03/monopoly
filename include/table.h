#ifndef TABLE_H
#define TABLE_H
#include "bot.h"
#include "human.h"

class Table {
private: 
    int map_[28];
    Player* players_[4];
};

#endif