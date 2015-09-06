#pragma once

#include "Core/Primitive.h"

class Cylinder: public Primitive{
public:
    Cylinder(int _layer = 0):
        Primitive(_layer){}
    Cylinder(double cx, double cy, double cz, double r, double h, int _layer = 0);

    PRIMITIVE_FUNC

    BoundingBox baseBoundingBox()
        {return BoundingBox(-1, -1, -1, 1, 1, 1);}
};
