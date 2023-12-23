#include "game.h"

#include <iostream>

Game::Game(const std::string& arg) /* : human_(), bot_{Bot(), Bot(), Bot(), Bot()}*/ {
	if (arg.compare("human")) { gameType_ = 0; }
	else if(arg.compare("computer")) { gameType_ = 1; }
	else { throw std::invalid_argument("Invalid game type argument : " + arg); }

	// Table va inizializzata in base alla modalità di gioco quindi nel
	// caso gameType == 0 (PvE) viene inizzializzata con 3 bot e un umano (prende i puntatori)
	// altrimenti (gameType == 1) (EvE) viene inizializzata con 4 bot (prende i puntatori)
}

void Game::run() {
	std::cout << "Welcome to Monopoly!" << std::endl;
}