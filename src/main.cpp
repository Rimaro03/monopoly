#include <iostream>
#include "game.h"

int main(int argc, char* argv[]) {
    if (argc != 2) { throw std::invalid_argument("args count must be 1!"); }

    Game::Init(argv[1]);
    Game::Run();
    return 0;
}