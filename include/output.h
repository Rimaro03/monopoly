#ifndef OUTPUT
#define OUTPUT

#include "table.h"
#include <fstream>

class Output
{
public:
	Output();
	~Output();

	void updateLog(/*BOH?*/);
	void printTable(const Table& table);
	void printList(const Table& player);
	void printBalances(const Table& table);
	void printCommandError(const std::string& command);

private:
	std::ofstream gameLog_;

	void clearConsole();
};

#endif // !OUTPUT
