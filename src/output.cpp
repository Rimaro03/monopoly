#include "output.h"

#include <iostream>
#include <string>

#include "game.h"

Output::Output(): gameLog_("log.txt", std::fstream::out) { }
Output::~Output() { gameLog_.close(); }

void Output::updateLog(const std::string& message) {
	gameLog_ << message << "\n";
}
void Output::printTable(Table& table) {
	clearConsole();
	std::cout << "Feature not completed \n";
	
	constexpr int TABLE_SIZE = 9;
	std::string** table_str = new std::string*[TABLE_SIZE];
	for(int i = 0; i < TABLE_SIZE; i++){ table_str[i] = new std::string[TABLE_SIZE]; }

	for (int i = 1; i < TABLE_SIZE; i++) { table_str[0][i].append("   ").append(std::to_string(i)).append("   "); }
	for (int i = 1; i < TABLE_SIZE; i++) { 
		table_str[i][0].append("   "); 
		table_str[i][0] += (char)(i - 1 + 'A');
		table_str[i][0].append("   ");
	}
	table_str[0][0] = "       ";
	for (int i = 1; i < TABLE_SIZE; i++) {
		for (int j = 1; j < TABLE_SIZE; j++) {
			table_str[i][j] = "       ";
		}
	}

	for (int pos = 0; pos < 28; pos++) {
		int x;
		int y;
		if (pos < 8) { x = pos + 1; y = 1; }
		else if (pos < 14) { x = 8; y = pos - 6; }
		else if (pos < 22) { x = 22 - pos; y = 8; }
		else /*pos < 28*/ { x = 1; y = 29 - pos; }

		if (pos % 7 != 0) { table_str[y][x] = " | L | "; } // DEBUG
		else { table_str[y][x] = " | A | "; }
		/*
		get box[pos] info from table
		*/
	}

	for (int i = 0; i < TABLE_SIZE; i++) {
		for (int j = 0; j < TABLE_SIZE; j++) {
			std::cout << table_str[i][j];
		}
		std::cout << "\n\n\n";
	}
	std::cout << std::endl;

	for(int i = 0; i < TABLE_SIZE; i++){ delete[] table_str[i]; }
	delete[] table_str;
}
void Output::printList(Table& table) {
	clearConsole();
	std::cout << "Feature not implemented\n";
	/*
	for(Player* p : table){
		std::cout << p->name() << ": ";
		for(Box owned by p){ std::cout << box << ", "; }
		std::cout << "\b\b  \n";	
	}
	*/
}
void Output::printBalances(Table& table) {
	clearConsole();	
	Game::Log("Balances:");
	for (auto p = table.BeginPlayer(); p != table.EndPlayer(); ++p) {
		Game::Log("Player " + std::to_string((*p).ID()) + " : " + std::to_string((*p).balance()) + "$");
	}

}
void Output::printCommandError(const std::string& command) {
	clearConsole();
	Game::Log(command + " is not a recognized command!");
}

void Output::clearConsole() { system("cls"); }