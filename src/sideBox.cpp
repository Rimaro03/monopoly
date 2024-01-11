/**
 * @author: Leonardo Ongaro - 2074985
*/

#include "sideBox.h"

SideBox::SideBox(const unsigned int ID, const bool start): Box::Box{ID}, start_{start} {}

void SideBox::start(bool st)
{
    start_ = st;
}

bool SideBox::start() const
{
    return start_;
}