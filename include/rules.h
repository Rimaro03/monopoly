// Filippo Battisti 2066659

#ifndef RULE_H
#define RULE_H

constexpr int PLAYERS_COUNT = 4; // numero di giocatori
constexpr int BOARD_SIZE = 8; // numero di caselle per lato
constexpr int BOXES_PER_ROW = BOARD_SIZE - 1; // numero di caselle per lato esclusa l'ultima
constexpr int BOX_COUNT = BOXES_PER_ROW * 4; // numero di caselle totali
constexpr int START_PASS_BONUS = 20; // bonus per il passaggio dal via
constexpr int START_BALANCE = 100; // saldo iniziale
constexpr int ECONOMIC_BOXES_COUNT = 8; // numero di caselle economiche
constexpr int STANDARD_BOXES_COUNT = 10; // numero di caselle standard
constexpr int LUXURY_BOXES_COUNT = 6; // numero di caselle lusso
constexpr int MAX_BOT_GAME_TURNS = 10; // numero massimo di turni per partita tra bot

constexpr int TERRAIN_COST[3] = { 6, 10, 20 }; // prezzi dei terreni per ogni tipo di terreno (economico, standard, lusso)
constexpr int HOUSE_COST[3] = { 3, 5, 10 }; // prezzi delle case per ogni tipo di terreno (economico, standard, lusso)
constexpr int HOTEL_COST[3] = { 3, 5, 10 }; // prezzi degli alberghi per ogni tipo di terreno (economico, standard, lusso)
constexpr int HOUSE_RENT[3] = { 2, 4, 7 }; // prezzi degli affitti delle case per ogni tipo di terreno (economico, standard, lusso)
constexpr int HOTEL_RENT[3] = { 4, 8, 14 }; // prezzi degli affitti degli alberghi per ogni tipo di terreno (economico, standard, lusso)

#endif // !RULE_H
