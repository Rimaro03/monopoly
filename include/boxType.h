#ifndef BOXTYPE_H
#define BOXTYPE_H

#include "LateralBox.h"

namespace BoxType{
    class Economic: public LateralBox{
        public:
            Economic();
    };

    class Standard: public LateralBox{
        public:
            Standard();
    };

    class Luxury: public LateralBox{
        public:
            Luxury();
    };
}

#endif