#include "player.h"
#include "game.h"

/* Constructors */
Player::Player(const unsigned int ID, int balance) : ID_{ID}, balance_{balance} {
    indexMove_ = 0;
}

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
    Game::Log("- Giocatore " + std::to_string(ID()) + " è arrivato alla casella " + Game::GetCoordinate(indexMove_));
}

const unsigned int Player::ID() {
    return ID_;
}

std::vector<LateralBox*>* Player::properties() {
    return &properties_;
}

/* Actions */

void Player::move() {
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    Game::Log("- Giocatore " + std::to_string(ID()) + " ha tirato i dadi ottenendo un valore di " + std::to_string(dice1 + dice2));
    indexMove((indexMove_ + dice1 + dice2) % 28);
}
bool Player::buy(LateralBox& box) {
    if(balance() - box.price() < 0){
        return false;
    } else {
        balance(balance() - box.price());
        properties_.push_back(&box);
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

