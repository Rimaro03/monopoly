// Author: Davide Tonolotto - 2073997

#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"
#include <array>
#include <cctype>

class Human : public Player {
public:
    /**
     * @param ID the ID of the player
     * @param balance the starting balance of the player
    */
    Human(const unsigned int ID, int balance);

    /**
     * @param table pointer to the table
     * The turn of the human player 
     * Available commands:
     * `show`: show the all the information about the players
     * `show table`: show the table
     * `show balances`: show the balances of the players
     * `show list`: show the possesions of the players
    */
    void turn(Table* table) override;
};

#endif