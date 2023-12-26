#ifndef TABLE_H
#define TABLE_H
#include "bot.h"
#include "human.h"
#include "box.h"

class Table {
public:
    Table(Player* players);

private:
    Box map_[28];
    Player* players_;

};

#endif