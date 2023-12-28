#ifndef LATERALBOX_H
#define LATERALBOX_H
#include "box.h"
#include "boxType.h"
#include "declaration.h"

class LateralBox : public Box {
private:
    Player* owner_;
    const BoxType type_;
    int housePrice_;
    int price_;
    int hotelPrice_;

    int houseRent_;
    int hotelRent_;
    bool house_;
    bool hotel_;

    public: 
    LateralBox(const unsigned int ID, BoxType type);

    //TODO: invece di salvarmi tutto qua, mi riprendo i dati da rules.h tramite BoxType
    Player* owner() const;
    BoxType type() const;
    void owner(Player* owner);

    //TODO: basta un set/get price e un set/get rent
    int price() const;
    int housePrice() const;
    int hotelPrice() const;

    int houseRent() const;
    int hotelRent() const;

    bool house() const;
    bool hotel() const;
    void house(bool house);
    void hotel(bool hotel);
};

#endif

