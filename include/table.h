#ifndef TABLE_H
#define TABLE_H
#include "bot.h"
#include "human.h"
#include "box.h"

class Table {
private:
    Box map_[28];
    Player* players_;

public:
    Table(Player* players);
};

#endif