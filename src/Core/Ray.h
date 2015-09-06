#pragma once

#include "Utility/Arrays.h"

struct Ray{
public:
    static long long rayCount;

    Point o;
    Vector d;
    double tMin, tMax;
    long long timeStamp;

    Ray(Point _o = Point(0, 0, 0), Vector _d = Vector(0, 0, 1)):
        o(_o), d(_d), timeStamp(-1){}

    Ray &operator++();
};
