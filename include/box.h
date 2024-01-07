#ifndef BOX_H
#define BOX_H

class Box
{
private:
    unsigned int id_;

public:
    Box() = default;
    Box(unsigned int ID);
    virtual ~Box() = default;
    
    void id(unsigned int ID);
    unsigned int id() const;
    bool side();
};

#endif