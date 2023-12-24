#include "game.h"

#include <iostream>

Game::Game() : gameType_(-1) {}

Game& Game::Get() { 
	static Game instance_;
	return instance_; 
}
void Game::Init(const std::string& arg) { Get().init_Internal(arg); }
void Game::Run() { Get().run_Internal(); }
void Game::Command(const std::string& command) { Get().command_Internal(command); }
void Game::Log(const std::string& command) { Get().log_Internal(command); }

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
}
void Game::run_Internal() {
	if (!Game::Initialized()) { throw std::runtime_error("Game not initialized!"); }

	std::cout << "Welcome to monopoly!" << std::endl;

	/*
	while(//table.is_there_a_winner?){
		table.turn();
	}

	std::cout << "The winner is " << table.winner()->name() << "!" << std::endl;
	*/
}
void Game::log_Internal(const std::string& message) {
	if (!Game::Initialized()) { throw std::runtime_error("Game not initialized!"); }

	output_.updateLog(message);
}
void Game::command_Internal(const std::string& command) {
	if (!Game::Initialized()) { throw std::runtime_error("Game not initialized!"); }

	if (command == "show") {
		static int counter = 0;
		switch (counter % 3) {
		case 0: 
			/*output_.printTable(table_);*/
			std::cout << "Table printed" << std::endl;
			break;
		case 1:
			/*output_.printList(table_);*/
			std::cout << "List printed" << std::endl;
			break;
		case 2:
			/*output_.printBalances(table_);*/
			std::cout << "Balances printed" << std::endl;
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