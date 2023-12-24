#include "output.h"

#include <iostream>

Output::Output(): gameLog_("log.txt", std::fstream::out) { }
Output::~Output() { gameLog_.close(); }

void Output::updateLog(/*GameInfo*/) {
	//gameLog_ << GameInfo.message;
}
void Output::printTable(const Table& table) {
	std::cout << "Feature not implemented\n";
}
void Output::printList(const Player* player) {
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
void Output::printBalances(const Table& table) {
	clearConsole();
	std::cout << "Feature not implemented\n";
	/*
	std::cout << "Balances:\n";

	for(Player* p : table){
		std::cout << p->name() << ": " << p->balance() << "$\n";
	}
	*/
}

void Output::clearConsole() { system("cls"); }