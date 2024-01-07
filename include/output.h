//FILIPPO BATTISTI - 2066659

#ifndef OUTPUT
#define OUTPUT

#include <fstream>

#include "gametype.h"
#include "table.h"

constexpr int GRID_SIZE = BOARD_SIZE + 1;

class Output
{
public:
	Output();
	~Output();

	// inizializza il log di output in base al tipo di partita [pve (player vs entity), eve (entity vs entity)]
	void init(GameType gameType);
	// aggiorna il log di output
	void updateLog(const std::string& message);
	// stampa la tabella di gioco
	void printTable(Table& table);
	// stampa la lista dei giocatori e le loro proprietà
	void printList(Table& table);
	// stampa i bilanci dei giocatori
	void printBalances(Table& table);

private:
	bool isInitialized_; // indica se il log è stato inizializzato
	std::ofstream gameLog_; // log di output
	std::string grid[GRID_SIZE][GRID_SIZE]; // buffer necessario per stampare la tabella di gioco
};

#endif // !OUTPUT
