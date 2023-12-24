#ifndef OUTPUT
#define OUTPUT

#include "Table.h"
#include <fstream>

class Output
{
public:
	Output();
	~Output();

	void updateLog(const std::string& message);
	void printTable(const Table& table);
	void printList(const Table& table);
	void printBalances(const Table& table);
	void printCommandError(const std::string& command);

private:
	std::ofstream gameLog_;

	void clearConsole();
};

#endif // !OUTPUT
