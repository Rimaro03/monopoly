#include "game.h"

#include <iostream>

Game::Game() : gameType_(-1) { }

Game& Game::Get() { 
	static Game instance_;
	return instance_; 
}
void Game::Init(const std::string& arg) { Get().init_Internal(arg); }
void Game::Run() { Get().run_Internal(); }
void Game::Command(const std::string& command) { Get().command_Internal(command); }
void Game::UpdateLog(const std::string& message) { Get().updateLog_Internal(message); }
void Game::Log(const std::string& message) { Get().log_Internal(message); }

std::string Game::GetCoordinate(int position) { return Get().GetCoordinate_Internal(position); }

bool Game::Initialized() { return Get().gameType_ != -1; }

void Game::init_Internal(const std::string& arg) {
	//human_ = Human();
	//for (int i = 0; i < 4; i++) { bot_[i] = Bot(); }

	if (arg == "human") { gameType_ = 0; }
	else if (arg == "computer") { gameType_ = 1; }
	else { throw std::invalid_argument("Invalid game type argument : " + arg); }

	// Table va inizializzata in base alla modalità di gioco quindi nel
	// caso gameType == 0 (PvE) viene inizzializzata con 3 bot e un umano (prende i puntatori)
	// altrimenti (gameType == 1) (EvE) viene inizializzata con 4 bot (prende i puntatori)

	srand((unsigned int)time(NULL));
}
void Game::run_Internal() {
	if (!Game::Initialized()) { throw std::runtime_error("Game not initialized!"); }

	Log("Hello world!");

	/*
	while(//table.is_there_a_winner?){
		table.turn();
	}

	Log("The winner is " + table.winner()->name() + "!");
	*/
}
void Game::updateLog_Internal(const std::string& message) { output_.updateLog(message); }
void Game::command_Internal(const std::string& command) {
	if (!Game::Initialized()) { throw std::runtime_error("Game not initialized!"); }

	if (command == "show") {
		static int counter = 0;
		switch (counter % 3) {
		case 0: 
			/*output_.printTable(table_);*/
			Log("Table printed");
			break;
		case 1:
			/*output_.printList(table_);*/
			Log("List printed");
			break;
		case 2:
			/*output_.printBalances(table_);*/
			Log("Balances printed");
			break;
		default: 
			break;
		}
		counter++;
	}
	else {
		output_.printCommandError(command);
	}
}
void Game::log_Internal(const std::string& message) { std::cout << message << std::endl; }
std::string Game::GetCoordinate_Internal(int position) {
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