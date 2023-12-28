#include "lateralBox.h"
#include "player.h"
#include "rules.h"

LateralBox::LateralBox(const unsigned int ID, BoxType type)
    : Box::Box(ID), type_{type}, owner_{nullptr}
{
    price_ = TERRAIN_COST[type];
    housePrice_ = HOTEL_COST[type];
    hotelPrice_ = HOTEL_COST[type];

    houseRent_ = HOUSE_RENT[type];
    hotelRent_ = HOTEL_RENT[type];
}

Player *LateralBox::owner() const
{
    return owner_;
}

BoxType LateralBox::type() const
{
    return type_;
}

void LateralBox::owner(Player *owner)
{
    owner_ = owner;
}

int LateralBox::price() const
{
    return price_;
}

int LateralBox::housePrice() const
{
    return housePrice_;
}

int LateralBox::hotelPrice() const
{
    return hotelPrice_;
}

int LateralBox::houseRent() const
{
    return houseRent_;
}

int LateralBox::hotelRent() const
{
    return hotelRent_;
}

bool LateralBox::house() const
{
    return house_;
}

void LateralBox::house(bool house)
{
    house_ = house;
    hotel_ = false;
}

bool LateralBox::hotel() const
{
    return hotel_;
}

void LateralBox::hotel(bool hotel)
{
    hotel_ = hotel;
    house_ = false;
}