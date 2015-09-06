#pragma once

#include "Core/Primitive.h"

class Cuboid: public Primitive{
private:
    bool solve(const Ray &ray);
    bool solve(const Ray &ray, double &inMax, double &outMax, int &inTag, int &outTag);

public:
    Cuboid(int _layer = 0):
        Primitive(_layer){}
    Cuboid(double cx, double cy, double cz, double lx, double ly, double lz, int _layer = 0);

    PRIMITIVE_FUNC

    BoundingBox baseBoundingBox()
        {return BoundingBox(-1, -1, -1, 1, 1, 1);}
};
