//FILIPPO BATTISTI - 2066659

#include "game.h"

#include <iostream>
#include <string>
#include <algorithm>

#include "rules.h"
#include "player.h"
#include "human.h"

Game::Game() : gameType_(GameType::INVALID), human_(1, START_BALANCE), bots_{Bot(1, START_BALANCE), Bot(2, START_BALANCE), Bot(3, START_BALANCE), Bot(4, START_BALANCE)} {}

Game &Game::Get()
{
	static Game instance_;
	return instance_;
}
void Game::Init(const std::string &arg) { Get().init_Internal(arg); }
void Game::Run() { Get().run_Internal(); }
void Game::UpdateLog(const std::string &message) { Get().updateLog_Internal(message); }
void Game::Log(const std::string &message) { Get().log_Internal(message); }
void Game::Command(const std::string &command) { Get().command_Internal(command); }

bool Game::Initialized() { return Get().gameType_ != GameType::INVALID; }

void Game::choosePlayersTurnOrder(std::array<Player*, PLAYERS_COUNT>& player_ptrs)
{
	std::array<int, PLAYERS_COUNT> dices{};// inizializzo tutti i dadi a 0
	
	int player_ptr_index = 0;
	bool finished = false;
	while (!finished) // finche' non abbiamo un vincitore
	{
		int max = 0;
		int winner_count = 0;
		for (int i = 0; i < PLAYERS_COUNT; i++) // lancio dei dadi
		{
			if (dices[i] == -1) { continue; } // vuol dire che siamo al secondo lancio e il giocatore non e' tra i finalisti

			dices[i] = player_ptrs[i]->throwDice(); // lancia il dado
			if (dices[i] > max) { max = dices[i]; } // tiene aggiornato il punteggio massimo
		}
		for (int i = 0; i < PLAYERS_COUNT; i++) // determina i finalisti
		{
			if (dices[i] == max) // controlla se il giocatore ha ottenuto il punteggio massimo allora e' tra i finalisti
			{ 
				player_ptr_index = i;
				winner_count++;
			}
			else if (dices[i] < max) { dices[i] = -1; } // non e' tra i finalisti e il suo punteggio viene settato a -1
		}
		if (winner_count == 1) { finished = true; } // abbiamo un vincitore
	}

	// RIORDINA I GIOCATORI
	std::array<Player*, PLAYERS_COUNT> tmp{};
	for (int i = 0; i < PLAYERS_COUNT; i++) { tmp[i] = player_ptrs[i]; }
	for (int i = 0; i < PLAYERS_COUNT; i++) { player_ptrs[i] = tmp[(player_ptr_index + i) % PLAYERS_COUNT]; }
}

void Game::init_Internal(const std::string &arg)
{
	srand((unsigned int)time(NULL)); // inizializza il generatore di numeri casuali

	if (arg == "human") { gameType_ = GameType::PLAYER_VS_ENTITY; } 
	else if (arg == "computer") { gameType_ = GameType::ENTITY_VS_ENTITY; }
	else { throw std::invalid_argument("Invalid game type argument : " + arg); }

	output_.init(gameType_); // inizializza il log di output

	std::array<Player*, PLAYERS_COUNT> player_ptrs = { &bots_[0], &bots_[1], &bots_[2], &bots_[3] };
	if (gameType_ == GameType::PLAYER_VS_ENTITY) { player_ptrs[0] = &human_; }
	choosePlayersTurnOrder(player_ptrs); // sceglie l'ordine dei giocatori
	table_.players(player_ptrs); // assegna i giocatori al tavolo
}
void Game::run_Internal()
{
	if (!Game::Initialized()) { throw std::runtime_error("Game not initialized!"); }

	// gioco: finché non c'è un vincitore e, se è un game tra bot, non raggiungo il limite dei turni
	int turnsCount = 0;
	while (!table_.hasWinner() && (gameType_ == GameType::PLAYER_VS_ENTITY || turnsCount < MAX_BOT_GAME_TURNS))
	{
		table_.turn();
		turnsCount++;
	}

	printWinner();
}
void Game::updateLog_Internal(const std::string &message)
{
	output_.updateLog(message);
	Log(message);
}
void Game::log_Internal(const std::string &message) { std::cout << message << std::endl; }
void Game::command_Internal(const std::string& command)
{
	if (!Game::Initialized()) { throw std::runtime_error("Game not initialized!"); }

	if (command == "show") { 
		output_.printTable(table_);
		output_.printList(table_);
		output_.printBalances(table_);
	}
	else if (command == "show table") { output_.printTable(table_); }
	else if (command == "show list") { output_.printList(table_); }
	else if (command == "show balances") { output_.printBalances(table_); }
}

void Game::printWinner() {
	// determina il vincitore o i vincitori (partite tra bot finite in pareggio)
	std::array<int, PLAYERS_COUNT> balances{}; // inizializza l'array dei bilanci a 0
	for (int i = 0; i < PLAYERS_COUNT; i++) { balances[i] = table_.players().at(i)->balance(); } // assegna i bilanci dei giocatori

	std::array<Player*, PLAYERS_COUNT> winners{}; // inizializza l'array dei vincitori a nullptr
	int maxBalance = *std::max_element(balances.begin(), balances.end());
	for (int i = 0; i < PLAYERS_COUNT; i++)
	{
		if (table_.players().at(i)->balance() >= maxBalance)
		{
			winners[i] = table_.players().at(i);
		}
	}

	int winnersCount = PLAYERS_COUNT - std::count(winners.begin(), winners.end(), nullptr);
	if (winnersCount == 1) { // un solo vincitore
		for (Player* winner : winners)
		{
			if (!winner){ continue; }

			Game::UpdateLog("- Giocatore " + std::to_string(winner->ID()) + " ha vinto la partita");
			break;
		}
	}
	else if (winnersCount > 1) { // piu' vincitori
		std::string msg;
		Game::UpdateLog("- Partita finita in pareggio per ");
		for (Player* winner : winners)
		{
			if (!winner){ continue; }

			msg += " giocatore " + std::to_string(winner->ID()) + " ";
		}
		Game::UpdateLog(msg);
	}
	else { throw std::runtime_error("No winners!"); }
}

std::string Game::GetCoordinate(int position)
{
	std::string coordinates;
	coordinates.resize(2); // evita di allocare memoria ogni volta

	coordinates += (char)('@' + Y(position)); // '@' = 'A' - 1
	coordinates += (char)('0' + X(position)); // '0' = '1' - 1

	return coordinates;
}
int Game::X(int position)
{
	switch (position / BOXES_PER_ROW) {
		case 0: return BOXES_PER_ROW - position + 1;
		case 1: return 1;
		case 2: return position - BOXES_PER_ROW * 2 + 1;
		case 3: return BOXES_PER_ROW + 1;
		default: throw std::invalid_argument("Invalid position! : " + std::to_string(position));
	}
}
int Game::Y(int position)
{
	switch (position / BOXES_PER_ROW) {
		case 0: return BOXES_PER_ROW + 1;
		case 1: return BOXES_PER_ROW * 2 - position + 1;
		case 2: return 1;
		case 3: return position - BOXES_PER_ROW * 3 + 1;
		default: throw std::invalid_argument("Invalid position! : " + std::to_string(position));
	}
}