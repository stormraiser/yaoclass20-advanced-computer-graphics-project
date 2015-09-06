#pragma once

#include "Core/Primitive.h"

class Sphere: public Primitive{
public:
    Sphere(int _layer = 0):
        Primitive(_layer){}
    Sphere(double cx, double cy, double cz, double r, int _layer = 0);

    PRIMITIVE_FUNC

    BoundingBox baseBoundingBox()
        {return BoundingBox(-1, -1, -1, 1, 1, 1);}
};
