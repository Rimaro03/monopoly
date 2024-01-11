/**
 * @author: Leonardo Ongaro - 2074985
*/

#include "box.h"

class SideBox : public Box
{
private:
    bool start_;

public:
    /* Setters and Getters */
    void start(const bool st);
    bool start() const;

    /**
     * @brief create a new SideBox object
     * 
     * @param ID the unique id of the Box
     * @param st boolean value, identify the start side box
    */
    SideBox(const unsigned int ID, const bool st);
};