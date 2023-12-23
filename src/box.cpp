#include "box.h"

Box::Box(unsigned int ID): id_{ID} {}

void Box::id(unsigned int ID)
{
    id_ = ID;
}

unsigned int Box::id() const {
    return id_;
}