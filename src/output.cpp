#include "output.h"

#include <iostream>
#include <string>

#include "game.h"

Output::Output() : gameLog_("log.txt", std::fstream::out) { }
Output::~Output() { gameLog_.close(); }

void Output::updateLog(const std::string& message) {
	gameLog_ << message << "\n";
}
void Output::printTable(Table& table) {
	// ------------------------ CREATE BUFFER ---------------------------

	constexpr int TABLE_SIZE = 9;
	std::string** table_str = new std::string * [TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++) { table_str[i] = new std::string[TABLE_SIZE]; }

	// ------------- SET BUFFER ------------

	for (int i = 0; i < TABLE_SIZE; i++) { // clear all
		for (int j = 0; j < TABLE_SIZE; j++) {
			table_str[i][j] = "          ";
		}
	}
	for (char i = 1; i < (char)TABLE_SIZE; i++) { // NUMERI E LETTERE (COORDINATE)
		table_str[i][0][2] = '@' + i;
		table_str[0][i][2] = '0' + i;
	}

	// ----------------SET ANGULAR BOXES-------------

	table_str[1][1] = "  |    |  ";
	table_str[TABLE_SIZE - 1][1] = "  |    |  ";
	table_str[1][TABLE_SIZE - 1] = "  |    |  ";
	table_str[TABLE_SIZE - 1][TABLE_SIZE - 1] = "  |    |  ";

	// -----------------SET LATERAL BOXES-----------------
	for (int i = 2; i < TABLE_SIZE - 1; i++) {
		table_str[1][i] = " |      | ";
		table_str[i][1] = " |      | ";
		table_str[TABLE_SIZE - 1][i] = " |      | ";
		table_str[i][TABLE_SIZE - 1] = " |      | ";
	}


	for (Box* box : table.map()) {
		int x = Game::X(box->id());
		int y = Game::Y(box->id());

		if (!box->side()) {
			char type;
			switch (((LateralBox*)box)->type()) {
			case luxury: type = 'L'; break;
			case standard: type = 'S'; break;
			case economic: type = 'E'; break;
			default: throw std::runtime_error("Invalid box type!");
			}

			char houseHotel = ' ';
			if (((LateralBox*)box)->house()) { houseHotel = '*'; }
			else if (((LateralBox*)box)->hotel()) { houseHotel = '^'; }

			table_str[y][x][2] = type; 
			table_str[y][x][3] = houseHotel;


		} // DEBUG
	}
	for (Player* p : table.players()) {
		int x = Game::X(p->indexMove());
		int y = Game::Y(p->indexMove());

		int character_position = (p->indexMove() % 7 == 0)? 3 : 4;
		while (table_str[y][x][character_position] != ' ') { character_position++; }
		table_str[y][x][character_position] = '0' + (char)p->ID();
	}

	// --------------- PRINT BUFFER -------------------

	for (int i = 0; i < TABLE_SIZE; i++) {
		for (int j = 0; j < TABLE_SIZE; j++) {
			std::cout << table_str[i][j];
		}
		std::cout << "\n\n\n\n";
	}
	std::cout << std::endl;

	// ---------------------- DELETE BUFFER --------------------

	for (int i = 0; i < TABLE_SIZE; i++) { delete[] table_str[i]; }
	delete[] table_str;
}
void Output::printList(Table& table) {
	Game::Log("Possessions :");
	for (Player* pp : table.players())
	{
		std::string msg = "Player " + std::to_string(pp->ID()) + " : ";
		for (Box* pb : table.map()) {
			if (pb->side()) { continue; }

			if (((LateralBox*)(pb))->owner() == pp) {
				msg += Game::GetCoordinate(pb->id()) + " ";
			}
		}
		Game::Log(msg);
	}
	Game::Log("");
}
void Output::printBalances(Table& table) {
	Game::Log("Balances:");
	for (Player* p : table.players()) {
		Game::Log("Player " + std::to_string(p->ID()) + " : " + std::to_string(p->balance()) + "$");
	}
	Game::Log("");
}
void Output::printCommandError(const std::string& command) {
	Game::Log(command + " is not a recognized command!");
}