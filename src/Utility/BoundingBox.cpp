#include "Utility/BoundingBox.h"
#include "Utility/Arrays.h"

BoundingBox &BoundingBox::extend(const Point &point){
    if (point.x < x1)
        x1 = point.x;
    if (point.x > x2)
        x2 = point.x;
    if (point.y < y1)
        y1 = point.y;
    if (point.y > y2)
        y2 = point.y;
    if (point.z < z1)
        z1 = point.z;
    if (point.z > z2)
        z2 = point.z;
    return *this;
}

BoundingBox &BoundingBox::extend(const BoundingBox &box){
    BoundingBox b;
    if (box.x1 < x1)
        x1 = box.x1;
    if (box.x2 > x2)
        x2 = box.x2;
    if (box.y1 < y1)
        y1 = box.y1;
    if (box.y2 > y2)
        y2 = box.y2;
    if (box.z1 < z1)
        z1 = box.z1;
    if (box.z2 > z2)
        z2 = box.z2;
    return *this;
}

BoundingBox &BoundingBox::intersect(const BoundingBox &box){
    BoundingBox b;
    if (box.x1 > x1)
        x1 = box.x1;
    if (box.x2 < x2)
        x2 = box.x2;
    if (box.y1 > y1)
        y1 = box.y1;
    if (box.y2 < y2)
        y2 = box.y2;
    if (box.z1 > z1)
        z1 = box.z1;
    if (box.z2 < z2)
        z2 = box.z2;
    return *this;
}

bool BoundingBox::disjoint(const BoundingBox &box) const{
    return (x2 < box.x1) || (x1 > box.x2) || (y2 < box.y1) || (y1 > box.y2) || (z2 < box.z1) || (z1 > box.z2);
}

Point BoundingBox::vertex(int k) const{
    switch (k){
        case 0: return Point(x1, y1, z1);
        case 1: return Point(x1, y1, z2);
        case 2: return Point(x1, y2, z1);
        case 3: return Point(x1, y2, z2);
        case 4: return Point(x2, y1, z1);
        case 5: return Point(x2, y1, z2);
        case 6: return Point(x2, y2, z1);
        case 7: return Point(x2, y2, z2);
    }
}

BoundingBox BoundingBox::octant(int k) const{
    switch (k){
        case 0: return BoundingBox(           x1,            y1,            z1, (x1 + x2) / 2, (y1 + y2) / 2, (z1 + z2) / 2);
        case 1: return BoundingBox(           x1,            y1, (z1 + z2) / 2, (x1 + x2) / 2, (y1 + y2) / 2,            z2);
        case 2: return BoundingBox(           x1, (y1 + y2) / 2,            z1, (x1 + x2) / 2,            y2, (z1 + z2) / 2);
        case 3: return BoundingBox(           x1, (y1 + y2) / 2, (z1 + z2) / 2, (x1 + x2) / 2,            y2,            z2);
        case 4: return BoundingBox((x1 + x2) / 2,            y1,            z1,            x2, (y1 + y2) / 2, (z1 + z2) / 2);
        case 5: return BoundingBox((x1 + x2) / 2,            y1, (z1 + z2) / 2,            x2, (y1 + y2) / 2,            z2);
        case 6: return BoundingBox((x1 + x2) / 2, (y1 + y2) / 2,            z1,            x2,            y2, (z1 + z2) / 2);
        case 7: return BoundingBox((x1 + x2) / 2, (y1 + y2) / 2, (z1 + z2) / 2,            x2,            y2,            z2);
    }
}

BoundingBox BoundingBox::rayIntersection(const Ray &ray) const{
    double tx1, tx2, ty1, ty2, tz1, tz2;
    if (ray.d.x > 0){
        tx1 = (x1 - ray.o.x) / ray.d.x;
        tx2 = (x2 - ray.o.x) / ray.d.x;
    }
    else{
        tx1 = (x2 - ray.o.x) / ray.d.x;
        tx2 = (x1 - ray.o.x) / ray.d.x;
    }
    if (ray.d.y > 0){
        ty1 = (y1 - ray.o.y) / ray.d.y;
        ty2 = (y2 - ray.o.y) / ray.d.y;
    }
    else{
        ty1 = (y2 - ray.o.y) / ray.d.y;
        ty2 = (y1 - ray.o.y) / ray.d.y;
    }
    if (ray.d.z > 0){
        tz1 = (z1 - ray.o.z) / ray.d.z;
        tz2 = (z2 - ray.o.z) / ray.d.z;
    }
    else{
        tz1 = (z2 - ray.o.z) / ray.d.z;
        tz2 = (z1 - ray.o.z) / ray.d.z;
    }
    return BoundingBox(tx1, ty1, tz1, tx2, ty2, tz2);
}
