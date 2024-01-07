//FILIPPO BATTISTI - 2066659

#include "output.h"

#include <iostream>
#include <string>

#include "game.h"

Output::Output() : grid(), isInitialized_(false) { }
Output::~Output() { gameLog_.close(); }

void Output::init(GameType gameType) {
	if (isInitialized_) { return; } // se è gia inizializzato non fare nulla

	// controlla il tipo di gioco e inizializza il log di output
	if (gameType == GameType::PLAYER_VS_ENTITY) { gameLog_.open("pve_game_log.txt"); }
	else if (gameType == GameType::ENTITY_VS_ENTITY) { gameLog_.open("eve_game_log.txt"); }
	else { throw std::runtime_error("Invalid game type!"); }

	if (!gameLog_.is_open()) { throw std::runtime_error("Cannot open log file!"); } // controlla se il file è stato aperto correttamente
	isInitialized_ = true; // setta il flag di inizializzazione
}
void Output::updateLog(const std::string& message) {
	if(!isInitialized_) { throw std::runtime_error("Output not initialized!"); } // controlla se è stato inizializzato
	gameLog_ << message << "\n";
}
void Output::printTable(Table& table) {
	for (int i = 0; i < GRID_SIZE; i++) { // azzera tutte le stringhe del buffer con una stringa di spazi lunga 8
		for (int j = 0; j < GRID_SIZE; j++) {
			grid[i][j] = "        ";
		}
	}
	for (char i = 1; i < (char)GRID_SIZE; i++) { // inserisce le lettere e i numeri delle coordinate
		grid[i][0][2] = '@' + i; // ('A' + i - 1)
		grid[0][i][2] = '0' + i; // ('1' + i - 1)
	}
	grid[GRID_SIZE-1][GRID_SIZE-1][1] = 'P'; // inserisce la P di partenza

	// DISEGNA LE CLASSI DELLE CASELLE, CASE E ALBERGHI

	for (Box* box : table.map()) {
		// ottiene le coordinate della casella
		int x = Game::X(box->id());
		int y = Game::Y(box->id());

		grid[y][x][0] = '|'; // disegna il bordo sinistro di ogni casella

		if (!box->side()) { // se è una casella laterale disegna la classe a cui appartiene la casella (L = luxury, S = standard, E = economic)
			switch (((LateralBox*)box)->type()) {
			case luxury: 
				grid[y][x][1] = 'L'; 
				break;
			case standard: 
				grid[y][x][1] = 'S';
				break;
			case economic: 
				grid[y][x][1] = 'E';
				break;
			default: 
				throw std::runtime_error("Invalid box type!");
			}

			// se la casella ha una casa o un albergo disegna il simbolo corrispondente (* = casa, ^ = albergo)
			if (((LateralBox*)box)->house()) { grid[y][x][2] = '*'; }
			else if (((LateralBox*)box)->hotel()) { grid[y][x][2] = '^'; }
		}
	}

	// DISEGNA I GIOCATORI
	for (Player* p : table.players()) {
		// ottiene le coordinate della posizione del giocatore
		int x = Game::X(p->indexMove()); 
		int y = Game::Y(p->indexMove());

		int character_position = 1; // controlla a partire dalla posizione 1 se c'è un carattere diverso da spazio (alla posizione 0 c'è '|')
		while (grid[y][x][character_position] != ' ') { character_position++; }
		grid[y][x][character_position] = '0' + (char)p->ID(); // inserisce il numero del giocatore nello spazio vuoto trovato
	}

	// BORDI DESTRI DI TUTTE LE CASELLE
	for (Box* b : table.map()) {
		// ottiene le coordinate della casella
		int x = Game::X(b->id());
		int y = Game::Y(b->id());

		// parte dalla posizione 2 e avanza finchè non trova uno spazio 
		// (alla posizione 0 c'è la classe della casella, e alla posizione 1 dovrà comunque esserci uno spazio)
		int character_position = 2;
		while (grid[y][x][character_position] != ' ') { character_position++; }
		grid[y][x][character_position] = '|'; // inserisce il bordo destro della casella
	}

	// PRINTA DEFINITIVAMENTE IL BUFFER
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			std::cout << grid[i][j];
		}
		Game::Log("\n");
	}
	Game::Log("");
}
void Output::printList(Table& table) {
	// in table.players() i giocatori sono ordinati per ordine di turno quindi vanno riordinati
	std::array<Player*, PLAYERS_COUNT> players{};
	for (Player* p : table.players()) { players[p->ID() - 1] = p; } // inserisce i player in modo che siano ordinati per ID

	Game::Log("Possessions :");
	for (Player* p : players)
	{
		std::string msg = "Player " + std::to_string(p->ID()) + " : "; // msg = "Player (1/2/3/4) : "
		// riempie la stringa msg con le coordinate delle caselle possedute dal giocatore
		for (Box* pb : table.map()) {
			if (pb->side()) { continue; }

			if (((LateralBox*)(pb))->owner() == p) { // se è posseduta dal giocatore la aggiunge alla stringa convertendo l'ID in coordinate
				msg += Game::GetCoordinate(pb->id()) + " ";
			}
		}
		Game::Log(msg); // printa la riga dei possedimenti del giocatore
	}
	Game::Log(""); // aggiunge una riga vuota
}
void Output::printBalances(Table& table) {
	// in table.players() i giocatori sono ordinati per ordine di turno quindi vanno riordinati
	std::array<Player*, PLAYERS_COUNT> players{};
	for (Player* p : table.players()) { players[p->ID() - 1] = p; } // inserisce i player in modo che siano ordinati per ID

	Game::Log("Balances:");
	for (Player* p : players) {
		// se il giocatore ha perso inserisce "---" altrimenti il suo bilancio
		std::string money_str = p->balance() >= 0 ? std::to_string(p->balance()) + "$" : "---"; 
		Game::Log("Player " + std::to_string(p->ID()) + " : " + money_str);
	}
	Game::Log("");
}