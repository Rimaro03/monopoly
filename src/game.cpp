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
	std::array<int, PLAYERS_COUNT> dices{}; // initialize the dices array to 0
	
	int player_ptr_index = 0; // winner index
	bool finished = false;
	while (!finished) // Until we have a winner
	{
		int max = 0;
		int winner_count = 0;
		for (int i = 0; i < PLAYERS_COUNT; i++) // dice throw
		{
			if (dices[i] == -1) { continue; } // it means that the player is not a finalist

			dices[i] = player_ptrs[i]->throwDice(); // throw the dice
			if (dices[i] > max) { max = dices[i]; } // update the max dice thrown
		}
		for (int i = 0; i < PLAYERS_COUNT; i++) // determine the finalists
		{
			if (dices[i] == max) // check if the player has thrown the max value, if so is a finalist
			{ 
				player_ptr_index = i;
				winner_count++;
			}
			else if (dices[i] < max) { dices[i] = -1; } // the player is not a finalist, his dice is set to -1
		}
		if (winner_count == 1) { finished = true; } // we have a winner
	}

	// reorder the players pointer array
	std::array<Player*, PLAYERS_COUNT> tmp{};
	for (int i = 0; i < PLAYERS_COUNT; i++) { tmp[i] = player_ptrs[i]; }
	for (int i = 0; i < PLAYERS_COUNT; i++) { player_ptrs[i] = tmp[(player_ptr_index + i) % PLAYERS_COUNT]; }
}

void Game::init_Internal(const std::string &arg)
{
	srand((unsigned int)time(NULL)); // Initialize the random seed

	if (arg == "human") { gameType_ = GameType::PLAYER_VS_ENTITY; } 
	else if (arg == "computer") { gameType_ = GameType::ENTITY_VS_ENTITY; }
	else { throw std::invalid_argument("Invalid game type argument : " + arg); }

	output_.init(gameType_); // Initialize the output file

	std::array<Player*, PLAYERS_COUNT> player_ptrs{};
	for(int i = 0; i < PLAYERS_COUNT; i++) { player_ptrs[i] = &bots_[i]; } // assign the bots to the player pointer array
	if (gameType_ == GameType::PLAYER_VS_ENTITY) { player_ptrs[0] = &human_; }
	choosePlayersTurnOrder(player_ptrs);
	table_.players(player_ptrs); // assign the players to the table
}
void Game::run_Internal()
{
	if (!Game::Initialized()) { throw std::runtime_error("Game not initialized!"); }

	// play until there is a winner and, if it's a bot game, until the max turns count is reached
	int turnsCount = 0;
	while (!table_.hasWinner() && turnsCount < MAX_GAME_TURNS)
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
	// determine the winner or the winners (bot games ended in a tie)
	std::array<int, PLAYERS_COUNT> balances{}; // Initialize the balances array to 0
	for (int i = 0; i < PLAYERS_COUNT; i++) { balances[i] = table_.players().at(i)->balance(); } // assign the balances to the balances array

	std::array<Player*, PLAYERS_COUNT> winners{}; // initialize the winners array to nullptr
	int maxBalance = *std::max_element(balances.begin(), balances.end());
	for (int i = 0; i < PLAYERS_COUNT; i++)
	{
		if (table_.players().at(i)->balance() >= maxBalance)
		{
			winners[i] = table_.players().at(i);
		}
	}

	int winnersCount = PLAYERS_COUNT - std::count(winners.begin(), winners.end(), nullptr);
	if (winnersCount == 1) { // One winner
		for (Player* winner : winners)
		{
			if (!winner){ continue; }

			Game::UpdateLog("- Giocatore " + std::to_string(winner->ID()) + " ha vinto la partita");
			break;
		}
	}
	else if (winnersCount > 1) { // More than one winner
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
	coordinates.resize(2);

	coordinates += (char)('@' + Y(position)); // '@' = 'A' - 1
	coordinates += (char)('0' + X(position)); // '0' = '1' - 1

	return coordinates;
}
int Game::X(int position)
{
	switch (position / BOXES_PER_ROW) {
		case 0: return BOXES_PER_ROW - position + 1; // low row
		case 1: return 1; // left column
		case 2: return position - BOXES_PER_ROW * 2 + 1; // top row
		case 3: return BOXES_PER_ROW + 1; // right column
		default: throw std::invalid_argument("Invalid position! : " + std::to_string(position));
	}
}
int Game::Y(int position)
{
	switch (position / BOXES_PER_ROW) {
		case 0: return BOXES_PER_ROW + 1; // low row
		case 1: return BOXES_PER_ROW * 2 - position + 1; // left column
		case 2: return 1; // top row
		case 3: return position - BOXES_PER_ROW * 3 + 1; // right column
		default: throw std::invalid_argument("Invalid position! : " + std::to_string(position));
	}
}