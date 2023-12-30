#ifndef LATERALBOX_H
#define LATERALBOX_H
#include "box.h"
#include "boxType.h"
#include "declaration.h"

class LateralBox : public Box
{
private:
    const BoxType type_;
    Player *owner_;

    int price_;

    int housePrice_;
    int hotelPrice_;

    int houseRent_;
    int hotelRent_;
    bool house_;
    bool hotel_;

public:
    LateralBox(const unsigned int ID, BoxType type);

    BoxType type() const;
    Player *owner() const;
    void owner(Player *owner);

    int price() const;
    int buildingPrice() const;
    int buildingRent() const;

    bool house() const;
    void house(bool house);
    bool hotel() const;
    void hotel(bool hotel);
};

#endif

