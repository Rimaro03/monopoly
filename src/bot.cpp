// Author: Davide Tonolotto - 2073997

#include "bot.h"
#include "game.h"
#include "rules.h"

Bot::Bot(const unsigned int ID, int balance) : Player(ID, balance) {}

void Bot::turn(Table* table){
    // Check if the player is still in the game
    if(balance() == -1) return;

    // if the player is in a negative balance he is eliminated
    // security check
    if(balance() < 0){
        Game::UpdateLog("- Giocatore " + std::to_string(ID()) + " e' stato eliminato");
        Player::removePlayer(table);
        return;
    }
    Player::move();

    // if the player pass the start box he get a bonus
    if(indexMove() < Player::lastPosition()){
        balance(balance() + START_PASS_BONUS);
        Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) +" e' passato dal via e ha ritirato " + std::to_string(START_PASS_BONUS) + " fiorini");
    }


    if(Player::indexMove() % 7 == 0){
        Player::endTurn();
        return;
    }

    std::array<Box*, BOX_COUNT>& boxMap = table->map();
    Box* boxUnknow = boxMap[indexMove()];
    LateralBox* box = (LateralBox*) boxUnknow;

    // ask the player if he want to buy the box
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
    // ask the player if he want to build a house or an hotel
    else if (box->owner() == this){
        if(box->house() && !box->hotel()){
            if(Player::balance() - box->buildingRent() >= 0){
                if(rand() % 4 == 0){
                    Player::balance(Player::balance() - box->buildingPrice());
                    box->hotel(true);
                    box->house(false);
                    Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + "  ha migliorato una casa in albergo sul terreno " + Game::GetCoordinate(indexMove()));
                }
            }
        } 
        else if(!box->house() && !box->hotel()){
            if(Player::balance() - box->buildingPrice() >= 0){
                if(rand() % 4 == 0){
                    Player::balance(Player::balance() - box->buildingPrice());
                    box->house(true);
                    Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + "  ha costruito una casa sul terreno " + Game::GetCoordinate(indexMove()));
                }
            }
        }
    }
    // if the player is not the owner of the box he has to pay the rent
    else if (box->owner() != this){
        if(Player::payPlayer(box->owner(), box)){
            if(box->hotel()){
                Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + " ha pagato " + std::to_string(box->buildingRent()) + " fiorini al giocatore " + std::to_string(box->owner()->ID()) + " per pernottamento nella casella " + Game::GetCoordinate(indexMove()));
            }
            else if(box->house()){
                Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + " ha pagato " + std::to_string(box->buildingRent()) + " fiorini al giocatore " + std::to_string(box->owner()->ID()) + " per pernottamento nella casella " + Game::GetCoordinate(indexMove()));
            }
        }
        else {
            Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + " e' stato eliminato");
            Player::removePlayer(table);
            return;
        }
    }

    Player::endTurn();
}