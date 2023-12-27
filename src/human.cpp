
#include "human.h"
#include "game.h"

Human::Human(const unsigned int ID, int balance) : Player(ID, balance) {}

void Human::turn(Table* table) {
    if(balance() < 0){
        Game::UpdateLog("- Giocatore " + std::to_string(ID()) + " e' stato eliminato");
        Player::removePlayer(table);
        return;
    }
    Player::move();

    if(indexMove() < Player::lastPosition()){
        balance(balance() + 20);
        Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) +" e' passato dal via e ha ritirato 20 fiorini");
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
            if(Player::balance() - box->houseRent() >= 0){
                std::string answer;
                do{
                    Game::Log("Vuoi costruire un albergo sulla casella " + Game::GetCoordinate(indexMove()) + " per " + std::to_string(box->hotelPrice()) + " fiorini? (s/n)");
                    std::cin >> answer;
                    if(answer == "show") Game::Show();
                } while((tolower(answer[0]) != 's' && tolower(answer[0]) != 'n') || answer.length() > 1);

                if(answer == "s"){
                    Player::balance(Player::balance() - box->hotelPrice());
                    box->hotel(true);
                    Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + "  ha migliorato una casa in albergo sul terreno " + Game::GetCoordinate(indexMove()));
                }
            }
        } 
        else if(!box->house() && !box->hotel()){
            if(Player::balance() - box->housePrice() >= 0){
                std::string answer;
                do{
                    Game::Log("Vuoi costruire una casa sulla casella " + Game::GetCoordinate(indexMove()) + " per " + std::to_string(box->housePrice()) + " fiorini? (s/n)");
                    std::cin >> answer;
                    if(answer == "show") Game::Show();
                } while((tolower(answer[0]) != 's' && tolower(answer[0]) != 'n') || answer.length() > 1);

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
            if(box->hotel()){
                Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + " ha pagato " + std::to_string(box->hotelRent()) + " fiorini al giocatore " + std::to_string(box->owner()->ID()) + " per pernottamento nella casella " + Game::GetCoordinate(indexMove()));
            }
            else if(box->house()){
                Game::UpdateLog("- Giocatore " + std::to_string(Player::ID()) + " ha pagato " + std::to_string(box->houseRent()) + " fiorini al giocatore " + std::to_string(box->owner()->ID()) + " per pernottamento nella casella " + Game::GetCoordinate(indexMove()));
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