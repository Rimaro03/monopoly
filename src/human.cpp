
#include "human.h"
#include "game.h"
#include "rules.h"

Human::Human(const unsigned int ID, int balance) : Player(ID, balance) {}

void Human::turn(Table* table) {
    if(balance() == -1) return;

    if(balance() < 0){
        Game::UpdateLog("- Giocatore " + std::to_string(ID()) + " e' stato eliminato");
        Player::removePlayer(table);
        return;
    }
    Player::move();

    if(indexMove() < Player::lastPosition()){
        balance(balance() + START_PASS_BONUS);
        Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) +" e' passato dal via e ha ritirato 20 fiorini");
    }

    if(Player::indexMove() % 7 == 0){
        Player::endTurn();
        return;
    }

    std::array<Box*, BOX_COUNT>& boxMap = table->map();
    Box* boxUnknow = boxMap[indexMove()];
    LateralBox* box = (LateralBox*) boxUnknow;

    if(box->owner() == nullptr){
        if(Player::balance() - box->price() >= 0){
            std::string answer;
            do {
                Game::Log("Vuoi comprare la casella " + Game::GetCoordinate(indexMove()) + " per " + std::to_string(box->price()) + " fiorini? (s/n)");
                std::cin >> answer;
                if(answer == "show") Game::Show();
            } while((tolower(answer[0]) != 's' && tolower(answer[0]) != 'n') || answer.length() > 1);

            if(answer == "s"){
                Player::buy(*box);
                Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + " ha acquistato il terreno " + Game::GetCoordinate(indexMove()));
            }
        } 
        Player::endTurn();
        return;
    }
    else if (box->owner() == this){
        if(box->house() && !box->hotel()){
            if(Player::balance() - box->buildingRent() >= 0){
                std::string answer;
                do{
                    Game::Log("Vuoi costruire un albergo sulla casella " + Game::GetCoordinate(indexMove()) + " per " + std::to_string(box->buildingPrice()) + " fiorini? (s/n)");
                    std::cin >> answer;
                    if(answer == "show") Game::Show();
                } while((tolower(answer[0]) != 's' && tolower(answer[0]) != 'n') || answer.length() > 1);

                if(answer == "s"){
                    Player::balance(Player::balance() - box->buildingPrice());
                    box->hotel(true);
                    Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + "  ha migliorato una casa in albergo sul terreno " + Game::GetCoordinate(indexMove()));
                }
            }
        } 
        else if(!box->house() && !box->hotel()){
            if(Player::balance() - box->buildingPrice() >= 0){
                std::string answer;
                do{
                    Game::Log("Vuoi costruire una casa sulla casella " + Game::GetCoordinate(indexMove()) + " per " + std::to_string(box->buildingPrice()) + " fiorini? (s/n)");
                    std::cin >> answer;
                    if(answer == "show") Game::Show();
                } while((tolower(answer[0]) != 's' && tolower(answer[0]) != 'n') || answer.length() > 1);

                if(answer == "s"){
                    Player::balance(Player::balance() - box->buildingPrice());
                    box->house(true);
                    Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + "  ha costruito una casa sul terreno " + Game::GetCoordinate(indexMove()));
                }
            }
        }
    }
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