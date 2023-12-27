#ifndef OUTPUT
#define OUTPUT

#include "table.h"
#include <fstream>

class Output
{
public:
	Output();
	~Output();

	void updateLog(const std::string& message);
	void printTable(Table& table);
	void printList(Table& table);
	void printBalances(Table& table);
	void printCommandError(const std::string& command);

private:
	std::ofstream gameLog_;

	void clearConsole();
};

#endif // !OUTPUT
