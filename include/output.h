//FILIPPO BATTISTI - 2066659

#ifndef OUTPUT
#define OUTPUT

#include <fstream>

#include "gametype.h"
#include "table.h"

/** @brief The size of the game board. */
constexpr int GRID_SIZE = BOARD_SIZE + 1;

class Output
{
public:
	Output();
	~Output();

	/** @brief Initialize the output log based on the game type. */
	void init(GameType gameType);
	/** @brief Updates the output log. */
	void updateLog(const std::string& message);
	/** @brief Prints the game board. */
	void printTable(Table& table);
	/** @brief Prints the list of player possessions. */
	void printList(Table& table);
	/** @brief Prints the players balances. */
	void printBalances(Table& table);

private:
	/** @brief True if the output has been initialized. */
	bool isInitialized_;
	/** @brief The output log file. */
	std::ofstream gameLog_;
	/** @brief The grid buffer of the game board needed to print it. */
	std::string** grid;
};

#endif // !OUTPUT
