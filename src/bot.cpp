#include "bot.h"
#include "game.h"

Bot::Bot(const unsigned int ID, int balance) : Player(ID, balance) {}

void Bot::turn(Table* table){
    if(balance() < 0){
        Game::UpdateLog("- Giocatore " + std::to_string(ID()) + " è stato eliminato");
        Player::removePlayer(table);
        return;
    }
    Player::move();

    if(indexMove() < Player::lastPosition()){
        balance(balance() + 20);
        Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) +" è passato dal via e ha ritirato 20 fiorini");
    }

    if(Player::indexMove() % 7 == 0){
        Player::endTurn();
        return;
    }

    std::array<Box*, 28> boxMap = table->map();
    Box* boxUnknow = boxMap[indexMove()];
    LateralBox* box = (LateralBox*) boxUnknow;

    if(box->owner() == nullptr){
        if(Player::balance() - box->price() >= 0){
            if(rand() % 4 == 0){
                Player::buy(*box);
                Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + " ha acquistato il terreno " + Game::GetCoordinate(indexMove()));
            }
        } 
        Player::endTurn();
        return;
    }
    else if (box->owner() == this){
        if(box->house() && !box->hotel()){
            if(Player::balance() - box->houseRent() >= 0){
                if(rand() % 4 == 0){
                    Player::balance(Player::balance() - box->hotelPrice());
                    box->hotel(true);
                    box->house(false);
                    Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + "  ha migliorato una casa in albergo sul terreno " + Game::GetCoordinate(indexMove()));
                }
            }
        } 
        else if(!box->house() && !box->hotel()){
            if(Player::balance() - box->housePrice() >= 0){
                if(rand() % 4 == 0){
                    Player::balance(Player::balance() - box->housePrice());
                    box->house(true);
                    Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + "  ha costruito una casa sul terreno " + Game::GetCoordinate(indexMove()));
                }
            }
        }
    }
    else if (box->owner() != this){
        if(Player::payPlayer(*(box->owner()), *box)){
            Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + " ha pagato " + std::to_string(box->hotelRent()) + " fiorini al giocatore " + std::to_string(box->owner()->ID()) + " per pernottamento nella casella " + Game::GetCoordinate(indexMove()));
        }
        else {
            Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + " e' stato eliminato");
            Player::removePlayer(table);
            return;
        }
    }

    Player::endTurn();
}