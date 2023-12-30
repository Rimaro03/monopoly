#include "game.h"

#include <iostream>
#include <string>
#include "rules.h"
#include "player.h"
#include "human.h"

Game::Game() : gameType_(-1), human_(1, START_BALANCE), bots_{Bot(1, START_BALANCE), Bot(2, START_BALANCE), Bot(3, START_BALANCE), Bot(4, START_BALANCE)} {}

Game &Game::Get()
{
	static Game instance_;
	return instance_;
}
void Game::Init(const std::string &arg) { Get().init_Internal(arg); }
void Game::Run() { Get().run_Internal(); }
void Game::Show() { Get().show_Internal(); }
void Game::UpdateLog(const std::string &message) { Get().updateLog_Internal(message); }
void Game::Log(const std::string &message) { Get().log_Internal(message); }

bool Game::Initialized() { return Get().gameType_ != -1; }

void Game::setPlayers()
{
	Player *player_ptrs[PLAYERS_COUNT] = {&bots_[0], &bots_[1], &bots_[2], &bots_[3]};
	if (gameType_ == 0)
	{
		player_ptrs[0] = &human_;
	}

	// LANCIO DEI DADI
	bool finished = false;
	int dices[PLAYERS_COUNT] = {0, 0, 0, 0};
	int player_ptrs_index = 0;
	while (!finished)
	{
		int max = 0;
		int winner_count = 0;
		for (int i = 0; i < PLAYERS_COUNT; i++) // throw dices
		{
			if (dices[i] == -1)
			{
				continue;
			} // vuol dire che siamo al secondo lancio e il giocatore non � tra i finalisti

			dices[i] = player_ptrs[i]->throwDice();
			if (dices[i] > max)
			{
				max = dices[i];
			}
		}
		for (int i = 0; i < PLAYERS_COUNT; i++) // determina i finalisti
		{
			if (dices[i] == max)
			{
				player_ptrs_index = i;
				winner_count++;
			}
			else if (dices[i] < max)
			{
				dices[i] = -1;
			} // non � tra i finalisti
		}
		if (winner_count == 1)
		{
			finished = true;
		} // abbiamo un vincitore
	}

	// RIORDINA I GIOCATORI
	Player *ordered_player_ptrs[PLAYERS_COUNT] = {nullptr, nullptr, nullptr, nullptr};
	for (int i = 0; i < PLAYERS_COUNT; i++)
	{
		ordered_player_ptrs[i] = player_ptrs[(player_ptrs_index + i) % PLAYERS_COUNT];
	}

	table_.players(ordered_player_ptrs);
}

void Game::init_Internal(const std::string &arg)
{
	srand((unsigned int)time(NULL));

	if (arg == "human")
	{
		gameType_ = 0;
	}
	else if (arg == "computer")
	{
		gameType_ = 1;
	}
	else
	{
		throw std::invalid_argument("Invalid game type argument : " + arg);
	}

	setPlayers();
}
void Game::run_Internal()
{
	if (!Game::Initialized())
	{
		throw std::runtime_error("Game not initialized!");
	}

	// gioco: finché non c'è un vincitore e, se è un game tra bot, non raggiungo il limite dei turni
	int turnsCount = 0;
	while (!table_.hasWinner() && (gameType_ == 1 ? turnsCount < MAX_BOT_GAME_TURNS : true))
	{
		table_.turn();
		if ((gameType_ == 1))
			turnsCount++;
	}

	// determina il vincitore
	for (Player *p : table_.players())
	{
		if (p->balance() >= 0)
		{
			Game::UpdateLog("- Giocatore " + std::to_string(p->ID()) + " ha vinto la partita");
			break;
		}
	}
}
void Game::updateLog_Internal(const std::string &message)
{
	output_.updateLog(message);
	Log(message);
}
void Game::show_Internal()
{
	if (!Game::Initialized())
	{
		throw std::runtime_error("Game not initialized!");
	}
	output_.printTable(table_);
	output_.printList(table_);
	output_.printBalances(table_);
}
void Game::log_Internal(const std::string &message) { std::cout << message << std::endl; }

std::string Game::GetCoordinate(int position)
{
	std::string coordinates;
	coordinates.resize(2);

	if (position < 7)
	{
		coordinates[0] = 'H';
		coordinates[1] = '8' - position;
	}
	else if (position < 14)
	{
		coordinates[0] = 'H' - position + 7;
		coordinates[1] = '1';
	}
	else if (position < 21)
	{
		coordinates[0] = 'A';
		coordinates[1] = '1' + position - 14;
	}
	else if (position < 28)
	{
		coordinates[0] = 'A' + position - 21;
		coordinates[1] = '8';
	}

	return coordinates;
}
int Game::X(int position)
{

	if (position < 8)
	{
		return 8 - position;
	}
	else if (position < 14)
	{
		return 1;
	}
	else if (position < 22)
	{
		return position - 13;
	}
	else /*pos < 28*/
	{
		return 8;
	}
}
int Game::Y(int position)
{
	if (position < 8)
	{
		return 8;
	}
	else if (position < 14)
	{
		return 15 - position;
	}
	else if (position < 22)
	{
		return 1;
	}
	else /*pos < 28*/
	{
		return position - 20;
	}
}