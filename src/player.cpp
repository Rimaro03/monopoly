#include "player.h"

/* Constructors */
Player::Player(const std::string& name, int balance) : name_{name}, balance_{balance}{}


/* Getter and setters */

int Player::indexMove() {
    return indexMove_;
}
int Player::balance() {
    return balance_;
}
void Player::balance(int balance) {
    balance_ = balance;
}
void Player::indexMove(int indexMove) {
    indexMove_ = indexMove;
}


/* Actions */

void Player::move() {
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    indexMove((indexMove_ + dice1 + dice2) % 28);
}
bool Player::buy(LateralBox& box) {
    if(balance() - box.price() < 0){
        return false;
    } else {
        balance(balance() - box.price());
        return true;
    }
}
bool Player::payPlayer(Player& player, LateralBox& box) {
    if(box.hotel()){
        if(balance() - box.hotelRent() < 0){
            player.balance(player.balance() + balance());
            return false;
        } else {
            balance(balance() - box.hotelRent());
            player.balance(player.balance() + box.hotelRent());
            return true;
        }
    } else if(box.house()){
        if(balance() - box.houseRent() < 0){
            player.balance(player.balance() + balance());
            return false;
        } else {
            balance(balance() - box.houseRent());
            player.balance(player.balance() + box.houseRent());
            return true;
        }
    } 
    return false;
}
bool Player::addHouse(LateralBox& box) {
    if(balance() - box.housePrice() >= 0 && !box.hotel() && !box.house()){
        balance(balance() - box.housePrice());
        box.house(true);
        return true;
    } 
    return false;
}
bool Player::addHotel(LateralBox& box) {
    if(balance() - box.hotelPrice() >= 0 && !box.hotel() && box.house()){
        balance(balance() - box.hotelPrice());
        box.hotel(true);
        return true;
    } 
    return false;
}