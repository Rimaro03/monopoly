#include "player.h"

#include "game.h"
#include "rules.h"

/* Constructors */
Player::Player(const unsigned int ID, int balance) : ID_{ID}, balance_{balance}
{
    indexMove_ = 0;
}

/* Getter and setters */

int Player::indexMove()
{
    return indexMove_;
}
int Player::balance()
{
    return balance_;
}
void Player::balance(int balance)
{
    balance_ = balance;
}
void Player::indexMove(int indexMove)
{
    indexMove_ = indexMove;
    Game::UpdateLog("- Giocatore " + std::to_string(ID()) + " e' arrivato alla casella " + Game::GetCoordinate(indexMove_));
}
int Player::lastPosition()
{
    return lastPosition_;
}
const unsigned int Player::ID()
{
    return ID_;
}

/* Actions */

void Player::move()
{
    int dice1 = throwDice();
    int dice2 = throwDice();
    Game::UpdateLog("- Giocatore " + std::to_string(ID()) + " ha tirato i dadi ottenendo un valore di " + std::to_string(dice1 + dice2));
    lastPosition_ = indexMove();
    indexMove((indexMove_ + dice1 + dice2) % BOX_COUNT);
}
bool Player::buy(LateralBox &box)
{
    if (balance() - box.price() < 0)
    {
        return false;
    }
    else
    {
        balance(balance() - box.price());
        box.owner(this);
        return true;
    }
}
bool Player::payPlayer(Player *player, LateralBox *box)
{
    if (box->hotel() && !box->house())
    {
        if (balance() - box->buildingRent() < 0)
        {
            player->balance(player->balance() + balance());
            return false;
        }
        else
        {
            balance(balance() - box->buildingRent());
            player->balance(player->balance() + box->buildingRent());
            return true;
        }
    }
    else if (box->house() && !box->hotel())
    {
        if (balance() - box->buildingRent() < 0)
        {
            player->balance(player->balance() + balance());
            return false;
        }
        else
        {
            balance(balance() - box->buildingRent());
            player->balance(player->balance() + box->buildingRent());
            return true;
        }
    }
    return true;
}

bool Player::addHouse(LateralBox &box)
{
    if (balance() - box.buildingPrice() >= 0 && !box.hotel() && !box.house())
    {
        balance(balance() - box.buildingPrice());
        box.house(true);
        return true;
    }
    return false;
}
bool Player::addHotel(LateralBox &box)
{
    if (balance() - box.buildingPrice() >= 0 && !box.hotel() && box.house())
    {
        balance(balance() - box.buildingPrice());
        box.hotel(true);
        return true;
    }
    return false;
}
int Player::throwDice()
{
    return rand() % 6 + 1;
}
void Player::endTurn()
{
    Game::UpdateLog("- Giocatore " + std::to_string(ID()) + " ha finito il turno");
}
void Player::removePlayer(Table *table)
{
    for (Box *box : table->map())
    {
        LateralBox *lateralBox = (LateralBox *)box;
        if (lateralBox->owner() == this)
        {
            lateralBox->owner(nullptr);
            lateralBox->house(false);
            lateralBox->hotel(false);
        }
    }
    this->balance(-1);
}