//FILIPPO BATTISTI - 2066659

#include "output.h"

#include <iostream>
#include <string>

#include "game.h"

Output::Output() : grid(), isInitialized_(false) { }
Output::~Output() { gameLog_.close(); }

void Output::init(GameType gameType) {
	if (isInitialized_) { return; }

	if (gameType == GameType::PLAYER_VS_ENTITY) { gameLog_.open("pve_game_log.txt"); }
	else if (gameType == GameType::ENTITY_VS_ENTITY) { gameLog_.open("eve_game_log.txt"); }
	else { throw std::runtime_error("Invalid game type!"); }

	if (!gameLog_.is_open()) { throw std::runtime_error("Cannot open log file!"); }
	isInitialized_ = true;
}
void Output::updateLog(const std::string& message) {
	if(!isInitialized_) { throw std::runtime_error("Output not initialized!"); }
	gameLog_ << message << "\n";
}
void Output::printTable(Table& table) {
	for (int i = 0; i < GRID_SIZE; i++) { // clear all
		for (int j = 0; j < GRID_SIZE; j++) {
			grid[i][j] = "        ";
		}
	}
	for (char i = 1; i < (char)GRID_SIZE; i++) { // NUMERI E LETTERE (COORDINATE)
		grid[i][0][2] = '@' + i;
		grid[0][i][2] = '0' + i;
	}
	grid[GRID_SIZE-1][GRID_SIZE-1][1] = 'P'; // PUNTO DI PARTENZA

	// DISEGNA LE CLASSI DELLE CASELLE, CASE E ALBERGHI

	for (Box* box : table.map()) {
		int x = Game::X(box->id());
		int y = Game::Y(box->id());

		// DISEGNA IL BORDO SINISTRO
		grid[y][x][0] = '|';

		if (!box->side()) {
			switch (((LateralBox*)box)->type()) {
			case luxury: 
				grid[y][x][1] = 'L'; 
				break;
			case standard: 
				grid[y][x][1] = 'S';
				break;
			case economic: 
				grid[y][x][1] = 'E';
				break;
			default: 
				throw std::runtime_error("Invalid box type!");
			}

			if (((LateralBox*)box)->house()) { grid[y][x][2] = '*'; }
			else if (((LateralBox*)box)->hotel()) { grid[y][x][2] = '^'; }
		} // DEBUG
	}

	// DISEGNA I GIOCATORI

	for (Player* p : table.players()) {
		int x = Game::X(p->indexMove());
		int y = Game::Y(p->indexMove());

		int character_position = 2;
		while (grid[y][x][character_position] != ' ') { character_position++; }
		grid[y][x][character_position] = '0' + (char)p->ID();
	}

	// BORDI SINISTRI DI TUTTE LE CASELLE
	for (Box* b : table.map()) {
		int x = Game::X(b->id());
		int y = Game::Y(b->id());

		int character_position = 2;
		while (grid[y][x][character_position] != ' ') { character_position++; }
		grid[y][x][character_position] = '|';
	}

	// --------------- PRINT -------------------

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			std::cout << grid[i][j];
		}
		Game::Log("\n");
	}
	Game::Log("");
}
void Output::printList(Table& table) {
	// in table.players() i giocatori sono ordinati per ordine di turno quindi vanno riordinati
	std::array<Player*, PLAYERS_COUNT> players = { nullptr, nullptr, nullptr, nullptr };
	for (Player* p : table.players()) { players[p->ID() - 1] = p; }

	Game::Log("Possessions :");
	for (Player* p : players)
	{
		std::string msg = "Player " + std::to_string(p->ID()) + " : ";
		for (Box* pb : table.map()) {
			if (pb->side()) { continue; }

			if (((LateralBox*)(pb))->owner() == p) {
				msg += Game::GetCoordinate(pb->id()) + " ";
			}
		}
		Game::Log(msg);
	}
	Game::Log("");
}
void Output::printBalances(Table& table) {
	// in table.players() i giocatori sono ordinati per ordine di turno quindi vanno riordinati
	std::array<Player*, PLAYERS_COUNT> players = { nullptr, nullptr, nullptr, nullptr };
	for (Player* p : table.players()) { players[p->ID() - 1] = p; }

	Game::Log("Balances:");
	for (Player* p : players) {
		std::string money_str = p->balance() >= 0 ? std::to_string(p->balance()) + "$" : "---";
		Game::Log("Player " + std::to_string(p->ID()) + " : " + money_str);
	}
	Game::Log("");
}