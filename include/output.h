//FILIPPO BATTISTI - 2066659

#ifndef OUTPUT
#define OUTPUT

#include <fstream>

#include "gametype.h"
#include "table.h"

constexpr int GRID_SIZE = 9;

class Output
{
public:
	Output();
	~Output();

	void init(GameType gameType);
	void updateLog(const std::string& message);
	void printTable(Table& table);
	void printList(Table& table);
	void printBalances(Table& table);

private:
	bool isInitialized_;
	std::ofstream gameLog_;
	std::string grid[GRID_SIZE][GRID_SIZE];
};

#endif // !OUTPUT
