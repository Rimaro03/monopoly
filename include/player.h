#ifndef PLAYER_H
#define PLAYER_H
#include "LateralBox.h"

class Player {
private:
    int indexMove_;
    int balance_;
    LateralBox* ownedBoxes_;
public:
    Player();
    ~Player();
};

#endif