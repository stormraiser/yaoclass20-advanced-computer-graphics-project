#pragma once

#include "Utility/def.h"
#include "Utility/Arrays.h"
#include "Core/Ray.h"
#include "Utility/func.h"

struct BoundingBox{
    double x1, y1, z1, x2, y2, z2;

    BoundingBox(double _x1 = INF, double _y1 = INF, double _z1 = INF, double _x2 = -INF, double _y2 = -INF, double _z2 = -INF):
        x1(_x1), y1(_y1), z1(_z1), x2(_x2), y2(_y2), z2(_z2){}

    bool empty() const
        {return (x1 > x2) || (y1 > y2) || (z1 > z2);}
    double volume() const
        {if (empty()) return 0; else return (x2 - x1) * (y2 - y1) * (z2 - z1);}
    bool intersectionEmpty() const
        {return (max3(x1, y1, z1) > min3(x2, y2, z2));}
    void intersectionInterval(double &tMin, double &tMax) const
        {tMin = max3(x1, y1, z1); tMax = min3(x2, y2, z2);}

    BoundingBox &extend(const Point &point);
    BoundingBox &extend(const BoundingBox &box);
    BoundingBox &intersect(const BoundingBox &box);
    bool disjoint(const BoundingBox &box) const;
    Point vertex(int k) const;
    BoundingBox octant(int k) const;
    BoundingBox rayIntersection(const Ray &ray) const;
};
