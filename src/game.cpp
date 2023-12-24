#include "game.h"

#include <iostream>

Game::Game() : gameType_(-1) {}

Game& Game::Get() { 
	static Game instance_;
	return instance_; 
}
void Game::Init(const std::string& arg) { Get().init_Internal(arg); }
void Game::Run() { Get().run_Internal(); }

void Game::init_Internal(const std::string& arg) {
	//human_ = Human();
	//for (int i = 0; i < 4; i++) { bot_[i] = Bot(); }

	if (arg.compare("human")) { gameType_ = 0; }
	else if (arg.compare("computer")) { gameType_ = 1; }
	else { throw std::invalid_argument("Invalid game type argument : " + arg); }

	// Table va inizializzata in base alla modalità di gioco quindi nel
	// caso gameType == 0 (PvE) viene inizzializzata con 3 bot e un umano (prende i puntatori)
	// altrimenti (gameType == 1) (EvE) viene inizializzata con 4 bot (prende i puntatori)
}
void Game::run_Internal() {
	if (gameType_ == -1) { throw std::runtime_error("Game not initialized!"); }

	std::cout << "Welcome to monopoly!" << std::endl;

	/*
	while(//table.is_there_a_winner?){
		table.turn();
	}

	std::cout << "The winner is " << table.winner()->name() << "!" << std::endl;
	*/
}