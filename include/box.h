/**
 * @author: Leonardo Ongaro - 2074985
*/

#ifndef BOX_H
#define BOX_H

class Box
{
private:
    unsigned int id_;

public:
    /**
     * @brief default constructor for Box
    */
    Box() = default;
    /**
     * @brief Construct a new Box object
     * 
     * @param ID the unique id for the Box
    */
    Box(unsigned int ID);
    /**
     * @brief default destructor for Box. Overwritten in LateralBox
    */
    virtual ~Box() = default;
    
    /* Setters and Getters */
    void id(unsigned int ID);
    unsigned int id() const;
    bool side();
};

#endif