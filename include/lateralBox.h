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
    virtual int Price();
    virtual int HousePrice();
    virtual int HotelPrice();
    virtual bool House();
    virtual bool Hotel();
    virtual void House(bool house);
    virtual void Hotel(bool hotel);
};