#ifndef BOX_H
#define BOX_H

class Box
{
private:
    unsigned int id_;

public:
    Box() = default;
    Box(unsigned int ID);
    void id(unsigned int ID);
    unsigned int id() const;
};

#endif