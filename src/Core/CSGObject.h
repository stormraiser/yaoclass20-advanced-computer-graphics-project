#pragma once

#include "Core/GeometricObject.h"
#include "Core/PrimitivePtr.h"
#include <list>

#define OPERATOR_DEC(symbol)                                                   \
    CSGObject operator symbol(const CSGObject &a, const CSGObject &b);         \
    CSGObject operator symbol(const CSGObject &a, const PrimitivePtr &b);      \
    CSGObject operator symbol(const PrimitivePtr &a, const CSGObject &b);      \
    CSGObject operator symbol(const PrimitivePtr &a, const PrimitivePtr &b);

class CSGNode;
class Primitive;

using std::list;

class CSGObject: public GeometricObject{
public:
    mutable CSGNode *root;
    mutable list<Primitive*> plist;
    vector<HitPoint> hitList;

public:
    CSGObject():
        root(0){plist.clear();}
    CSGObject(PrimitivePtr primitivePtr);

    void translate(double dx, double dy, double dz);
    void rotate(double ang, double ax, double ay, double az);
    void scale(double sx, double sy, double sz);
    void shear(double dx, double dy, double dz, double sx, double sy, double sz);

    bool hit(Ray ray);
    bool hit(Ray ray, HitPoint &hitPoint);

    void generateBoundingBox();
    int checkBoundingBox(const BoundingBox &box);

    void setChildCSG();

    operator CSGObject*()
        {return new CSGObject(*this);}
};

OPERATOR_DEC(+)
OPERATOR_DEC(-)
OPERATOR_DEC(*)
OPERATOR_DEC(^)
