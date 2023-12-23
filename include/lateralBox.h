#include "box.h"

class LateralBox : public Box {
private:
    const int price_;
    const int housePrice_;
    const int hotelPrice_;

    const int house_rent_;
    const int hotel_rent_;
    bool house_;
    bool hotel_;

public: 
    LateralBox(const int price, const int housePrice, const int hotelPrice, const int house_rent, const int hotel_rent);
    virtual int price();
    virtual int housePrice();
    virtual int hotelPrice();
    virtual bool house();
    virtual bool hotel();
    virtual void house(bool house);
    virtual void hotel(bool hotel);
    virtual int houseRent();
    virtual int hotelRent();
};