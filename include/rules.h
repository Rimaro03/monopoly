#ifndef RULE_H
#define RULE_H

constexpr int PLAYERS_COUNT = 4;
constexpr int BOARD_SIZE = 5;
constexpr int BOXES_PER_ROW = BOARD_SIZE - 1;
constexpr int BOX_COUNT = BOXES_PER_ROW * 4;
constexpr int START_PASS_BONUS = 20;
constexpr int START_BALANCE = 100;
constexpr int ECONOMIC_BOXES_COUNT = 8;
constexpr int STANDARD_BOXES_COUNT = 10;
constexpr int LUXURY_BOXES_COUNT = 6;
constexpr int MAX_BOT_GAME_TURNS = 10;
constexpr int TERRAIN_COST[3] = { 6, 10, 20 };
constexpr int HOUSE_COST[3] = { 3, 5, 10 };
constexpr int HOTEL_COST[3] = { 3, 5, 10 };
constexpr int HOUSE_RENT[3] = { 2, 4, 7 };
constexpr int HOTEL_RENT[3] = { 4, 8, 14 };

#endif // !RULE_H
