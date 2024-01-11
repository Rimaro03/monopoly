/**
 * @author: Leonardo Ongaro - 2074985
*/

#include "box.h"

#include "rules.h"

Box::Box(unsigned int ID): id_{ID} {}

void Box::id(unsigned int ID)
{
    id_ = ID;
}

unsigned int Box::id() const {
    return id_;
}
bool Box::side()
{
    {return (id_ % BOXES_PER_ROW == 0); }
}