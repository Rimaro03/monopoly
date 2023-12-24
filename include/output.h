#ifndef OUTPUT
#define OUTPUT

#include "Table.h"
#include <fstream>

class Output
{
public:
	Output();
	~Output();

	void updateLog(/*BOH?*/);
	void printTable(const Table& table);
	void printList(const Player* player);
	void printBalances(const Table& table);

private:
	std::ofstream gameLog_;

	void clearConsole();
};

#endif // !OUTPUT
