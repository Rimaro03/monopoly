#include "lateralBox.h"
#include "player.h"
#include "rules.h"

LateralBox::LateralBox(const unsigned int ID, BoxType type)
    : Box::Box(ID), type_{type}, owner_{nullptr}, hotel_{false}, house_{false}
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

int LateralBox::buildingPrice() const
{
    if(!house() && !hotel())
    {
        return housePrice_;
    }
    else if(house())
    {
        return hotelPrice_;
    }
    else{
        return -1;
    }
}

int LateralBox::buildingRent() const
{
    if(house()){
        return houseRent_;
    }
    else if(hotel()){
        return hotelRent_;
    }
    else{
        return 0;
    }
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