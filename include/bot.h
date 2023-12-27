#ifndef BOT_H
#define BOT_H
#include "player.h"

class Bot: public Player {
private:

public:
    Bot(const unsigned int ID, int balance);
    void turn();
};

#endif