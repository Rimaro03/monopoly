/**
 * @author: Leonardo Ongaro - 2074985
 */

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
    /**
     * @brief Construct a new LateralBox object
     *
     * @param ID the unique id of the Box
     * @param type enum, type of lateral box (eco, standard, lux).
     */
    LateralBox(const unsigned int ID, BoxType type);

    /* Setters and Getters */
    BoxType type() const;
    Player *owner() const;
    void owner(Player *owner);
    void hotel(bool hotel);
    void house(bool house);

    /**
     * @brief get the price to buy the box
     * @return integer, lateral box price
    */
    int price() const;
    /**
     * @brief returns the price for the house if you can build a house, hotel price if you can build one or -1
     * @return integer, price of the building you can build, -1 if nothing can be built
     */
    int buildingPrice() const;
    /**
     * @brief returns the rent for the house if you there is a house, hotel rent if there is one built one or 0 if no rent
     * @return integer, rent of the building built on the box, 0 if no rent
     */
    int buildingRent() const;

    /**
     * @brief builds a house, set the hotel to false
    */
    bool house() const;
    /**
     * @brief builds a hotel, set the house to false
    */
    bool hotel() const;
};

#endif
