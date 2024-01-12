//FILIPPO BATTISTI - 2066659

#include "output.h"

#include <iostream>
#include <string>

#include "game.h"

Output::Output() : isInitialized_(false) {
	grid = new std::string*[GRID_SIZE]; // allocate the grid buffer
	for (int i = 0; i < GRID_SIZE; i++) { grid[i] = new std::string[GRID_SIZE]; }
}
Output::~Output() {
	if (gameLog_.is_open()) { gameLog_.close(); }
	for (int i = 0; i < GRID_SIZE; i++) { delete[] grid[i]; }
	delete[] grid;
}

void Output::init(GameType gameType) {
	if (isInitialized_) { return; } // if already initialized return

	if (gameType == GameType::PLAYER_VS_ENTITY) { gameLog_.open("pve_game_log.txt"); }
	else if (gameType == GameType::ENTITY_VS_ENTITY) { gameLog_.open("eve_game_log.txt"); }
	else { throw std::runtime_error("Invalid game type!"); }

	if (!gameLog_.is_open()) { throw std::runtime_error("Cannot open log file!"); }
	isInitialized_ = true;
}
void Output::updateLog(const std::string& message) {
	if(!isInitialized_) { throw std::runtime_error("Output not initialized!"); } // if not initialized throw an error
	gameLog_ << message << "\n";
}
void Output::printTable(Table& table) {
	for (int i = 0; i < GRID_SIZE; i++) { // clear the grid buffer to print the new table
		for (int j = 0; j < GRID_SIZE; j++) {
			grid[i][j] = "        ";
		}
	}
	for (char i = 1; i < (char)GRID_SIZE; i++) { // insert the coordinates of the table
		grid[i][0][2] = '@' + i; // ('A' + i - 1)
		grid[0][i][2] = '0' + i; // ('1' + i - 1)
	}
	grid[GRID_SIZE-1][GRID_SIZE-1][1] = 'P'; // insert the "P" in the bottom right corner

	// Print boxes, houses and hotels

	for (Box* box : table.map()) {
		// get the coordinates of the box
		int x = Game::X(box->id());
		int y = Game::Y(box->id());

		grid[y][x][0] = '|'; // print the left border of the box

		if (!box->side()) { // if is not an angular box (L = luxury, S = standard, E = economic)
			LateralBox* lateral_box = (LateralBox*)box; // in this case is safe to cast to LateralBox
			switch (lateral_box->type()) {
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

			// if the box has an house or an hotel prints it (* = casa, ^ = albergo)
			if (lateral_box->house()) { grid[y][x][2] = '*'; }
			else if (lateral_box->hotel()) { grid[y][x][2] = '^'; }
		}
	}

	// Print players
	for (Player* p : table.players()) {
		int x = Game::X(p->indexMove()); 
		int y = Game::Y(p->indexMove());

		int character_position = 1; // check from position 1 where there is a space (at 0 there is '|')
		while (grid[y][x][character_position] != ' ') { character_position++; }
		grid[y][x][character_position] = '0' + (char)p->ID(); // insert the ID of the player in the box
	}

	// Print the right border of the boxes
	for (Box* b : table.map()) {
		int x = Game::X(b->id());
		int y = Game::Y(b->id());

		// Start from position 2 and check where there is a space
		int character_position = 2;
		while (grid[y][x][character_position] != ' ') { character_position++; }
		grid[y][x][character_position] = '|';
	}

	// Print all the buffer
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			std::cout << grid[i][j];
		}
		Game::Log("\n");
	}
	Game::Log("");
}
void Output::printList(Table& table) {
	// in table.players() players are ordered by turn order so they need to be reordered
	std::array<Player*, PLAYERS_COUNT> players{};
	for (Player* p : table.players()) { players[p->ID() - 1] = p; } // insert the players in order of ID

	Game::Log("Possessions :");
	for (Player* p : players)
	{
		std::string msg = "Player " + std::to_string(p->ID()) + " : "; // msg = "Player (1/2/3/4) : "
		// fills the string with the possessions of the player
		for (Box* pb : table.map()) {
			if (pb->side()) { continue; }

			if (((LateralBox*)(pb))->owner() == p) { // if is possessed by the player prints the coordinate of the box
				msg += Game::GetCoordinate(pb->id()) + " ";
			}
		}
		Game::Log(msg);
	}
	Game::Log("");
}
void Output::printBalances(Table& table) {
	// in table.players() players are ordered by turn order so they need to be reordered
	std::array<Player*, PLAYERS_COUNT> players{};
	for (Player* p : table.players()) { players[p->ID() - 1] = p; }

	Game::Log("Balances:");
	for (Player* p : players) {
		// if the balance is negative prints "---" else prints the balance
		std::string money_str = p->balance() >= 0 ? std::to_string(p->balance()) + "$" : "---"; 
		Game::Log("Player " + std::to_string(p->ID()) + " : " + money_str);
	}
	Game::Log("");
}