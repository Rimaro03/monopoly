#include "game.h"

#include <iostream>
#include <string>
#include "rules.h"
#include "player.h"
#include "human.h"

Game::Game() : gameType_(-1), human_(1, START_BALANCE), bot_{Bot(1, START_BALANCE), Bot(2, START_BALANCE), Bot(3, START_BALANCE), Bot(4, START_BALANCE)} { }

Game& Game::Get() { 
	static Game instance_;
	return instance_; 
}
void Game::Init(const std::string& arg) { Get().init_Internal(arg); }
void Game::Run() { Get().run_Internal(); }
void Game::Show() { Get().show_Internal(); }
void Game::UpdateLog(const std::string& message) { Get().updateLog_Internal(message); }
void Game::Log(const std::string& message) { Get().log_Internal(message); }

bool Game::Initialized() { return Get().gameType_ != -1; }

void Game::init_Internal(const std::string& arg) {
	if (arg == "human") { gameType_ = 0; }
	else if (arg == "computer") { gameType_ = 1; }
	else { throw std::invalid_argument("Invalid game type argument : " + arg); }

	if (gameType_ == 0) { table_.players(&human_, &bot_[1], &bot_[2], &bot_[3]); }
	else { table_.players(&bot_[0], &bot_[1], &bot_[2], &bot_[3]); }

	srand((unsigned int)time(NULL));
}
void Game::run_Internal() {
	if (!Game::Initialized()) { throw std::runtime_error("Game not initialized!"); }

	while(!table_.hasWinner()){
		table_.turn();
	}

	// determina il vincitore
	for (Player* p : table_.players()) {
		if (p->balance() >= 0) {
			Game::UpdateLog("- Giocatore " + std::to_string(p->ID()) + " ha vinto la partita");
			break;
		}
	}
}
void Game::updateLog_Internal(const std::string& message) { 
	output_.updateLog(message); 
	Log(message);
}
void Game::show_Internal() {
	if (!Game::Initialized()) { throw std::runtime_error("Game not initialized!"); }
	output_.printTable(table_);
	output_.printList(table_);
	output_.printBalances(table_);
}
void Game::log_Internal(const std::string& message) { std::cout << message << std::endl; }

std::string Game::GetCoordinate(int position) {
	std::string coordinates;
	coordinates.resize(2);

	if (position < 7) {
		coordinates[0] = 'H';
		coordinates[1] = '8' - position;
	}
	else if (position < 14) {
		coordinates[0] = 'H' - position + 7;
		coordinates[1] = '1';
	}
	else if (position < 21) {
		coordinates[0] = 'A';
		coordinates[1] = '1' + position - 14;
	}
	else if (position < 28) {
		coordinates[0] = 'A' + position - 21;
		coordinates[1] = '8';
	}

	return coordinates;
}
int Game::X(int position) {

	if (position < 8) { return 8 - position; }
	else if (position < 14) { return 1; }
	else if (position < 22) { return position - 13; }
	else /*pos < 28*/ { return 8; }
}
int Game::Y(int position) {
	if (position < 8) { return  8; }
	else if (position < 14) { return 15 - position; }
	else if (position < 22) { return 1; }
	else /*pos < 28*/ { return position - 20; }
}