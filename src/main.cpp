
#include <iostream>

#include "game.h"

int main() {
    int argc = 1;
    char* argv[] = { "human" }; // DEBUG

    if (argc != 1) { throw std::invalid_argument("args count must be 1!"); }
    Game game(argv[0]);
    game.run();
    return 0;
}