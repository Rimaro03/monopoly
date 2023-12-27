#include <array>
#include "human.h"
#include "game.h"

Human::Human(const unsigned int ID, int balance) : Player(ID, balance) {}

void Human::turn(Table* table) {
    if(balance() < 0){
        Game::UpdateLog("- Giocatore " + std::to_string(ID()) + " è stato eliminato");
        // remove player from Game
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
            Game::Log("Vuoi comprare la casella " + Game::GetCoordinate(indexMove()) + " per " + std::to_string(box->price()) + " fiorini? (s)");
            std::string answer;
            std::cin >> answer;
            if(answer == "s"){
                Player::buy(*box);
                Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + " ha acquistato il terreno " + Game::GetCoordinate(indexMove()));
            }
        } 
        Player::endTurn();
        return;
    }
    else if (box->owner() == this){
        // Should works, but I will test it later
        if(box->house()){
            if(Player::balance() - box->houseRent() >= 0){
                Game::Log("Vuoi costruire un albergo sulla casella " + Game::GetCoordinate(indexMove()) + " per " + std::to_string(box->hotelPrice()) + " fiorini? (s)");
                std::string answer;
                std::cin >> answer;
                if(answer == "s"){
                    Player::balance(Player::balance() - box->hotelPrice());
                    box->hotel(true);
                    box->house(false);
                    Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + "  ha migliorato una casa in albergo sul terreno " + Game::GetCoordinate(indexMove()));
                }
            }
        } 
        else {
            if(Player::balance() - box->housePrice() >= 0){
                Game::Log("Vuoi costruire una casa sulla casella " + Game::GetCoordinate(indexMove()) + " per " + std::to_string(box->housePrice()) + " fiorini? (s)");
                std::string answer;
                std::cin >> answer;
                if(answer == "s"){
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
            // remove player from Game
            return;
        }
    }

    Player::endTurn();
}