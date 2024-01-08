// Author: Davide Tonolotto - 2073997

#ifndef BOT_H
#define BOT_H
#include "player.h"

class Bot: public Player {
private:

public:
    /**
     * @param ID the ID of the player
     * @param balance the starting balance of the player
    */
    Bot(const unsigned int ID, int balance);

    /**
     * @param table pointer to the table
     * @brief The turn of the bot player
     * The bot will buy a box if it has enough money and if a random number is 0 (25% chance)
     * The bot will build a hotel if it has enough money and if a random number is 0 (25% chance)
     * The bot will build a house if it has enough money and if a random number is 0 (25% chance)
    */
    void turn(Table* table) override;
};

#endif