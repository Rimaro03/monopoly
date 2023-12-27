#include <iostream>
#include "game.h"

int main() {
    int argc = 1;
    const char* argv[] = { "human" }; // DEBUG

    if (argc != 1) { throw std::invalid_argument("args count must be 1!"); }

    Game::Init(argv[0]);
    Game::Run();

    return 0;
}