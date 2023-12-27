#ifndef LATERALBOX_H
#define LATERALBOX_H
#include "box.h"
#include "boxType.h"
#include "declaration.h"

class LateralBox : public Box {
private:
    Player* owner_;
    const BoxType type_;
    const int price_;
    const int housePrice_;
    const int hotelPrice_;

    const int houseRent_;
    const int hotelRent_;
    bool house_;
    bool hotel_;

    public: 
    LateralBox(const unsigned int ID, BoxType type, const int price, const int housePrice, const int hotelPrice, const int houseRent, const int hotelRent);

    Player* owner() const;
    void owner(Player* owner);

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

