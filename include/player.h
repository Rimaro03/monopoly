#ifndef PLAYER_H
#define PLAYER_H
#include "lateralBox.h"
#include <iostream>
#include <string>
#include <vector>

class Player {
private:
    int indexMove_;
    int balance_;
    const unsigned int ID_;  
    std::vector<LateralBox*> properties_;
public:
    /**
     * @brief Construct a new Player object
     * 
     * @param ID the ID of the player
     * @param balance the starting balance of the player
     * 
    */
    Player(const unsigned int ID, int balance);

    /* Getter and setters */
    int indexMove();
    int balance();
    const unsigned int ID();
    std::vector<LateralBox*>* properties();
    void balance(int balance);
    void indexMove(int indexMove);

    /* Actions */
    /**
     * @brief Move the player on the board by rolling two dices
    */
    void move();

    /**
     * @brief Buy a box
     * 
     * @param box the box to buy
     * @return true if the player can buy the box
     * @return false if the player can't buy the box
    */
    bool buy(LateralBox& box);

    /**
     * @brief Pay a player
     * 
     * @param player the player to pay
     * @param box the reason of the payment
     * @return true if the player can pay the player
     * @return false if the player can't pay the player
    */
    bool payPlayer(Player& player, LateralBox& box);

    /**
     * @brief Add a house to a box
     * 
     * @param box the box to add the house
     * @return true if the player can add a house
     * @return false if the player can't add a house
    */
    bool addHouse(LateralBox& box);
    /**
     * @brief Add an hotel to a box
     * 
     * @param box the box to add the hotel
     * @return true if the player can add an hotel
     * @return false if the player can't add an hotel
    */
    bool addHotel(LateralBox& box);
};

#endif