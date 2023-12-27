#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"
#include <array>
#include <cctype>

class Human : public Player {
public:
    Human(const unsigned int ID, int balance);

    void turn(Table* table) override;
};

#endif