#include "box.h"

class SideBox : Box
{
private:
    bool start_;

public:
    SideBox(const unsigned int ID, const bool st);
    void start(const bool st);
    bool start() const;
};