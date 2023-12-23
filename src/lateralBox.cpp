#include "lateralBox.h"

LateralBox::LateralBox(const unsigned int ID, const int price, const int housePrice, const int hotelPrice, const int houseRent, const int hotelRent)
    : Box::Box(ID), price_{price}, housePrice_{housePrice}, hotelPrice_{hotelPrice}, houseRent_{houseRent}, hotelRent_{hotelRent}
{
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