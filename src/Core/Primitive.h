#pragma once

#include "Core/GeometricObject.h"
#include "Utility/Arrays.h"
#include "Core/HitPoint.h"

#define PRIMITIVE_FUNC                                                    \
    bool hit(Ray ray);                                                    \
    bool hit(Ray ray, HitPoint &hitPoint);                                \
    bool hit(Ray ray, vector<HitPoint> &hitList);                         \
    int checkBoundingBox(const BoundingBox &box);                         \
    void getHitInfo(HitInfo &info);

#define CHECK_ROUTINE                                                     \
    if (box.disjoint(bBox))                                               \
        return Outside;                                                   \
    Point p;                                                              \
    double r;                                                             \
    transformBoundingBox(box, p, r);

class CSGPrimitiveNode;
class CSGObject;

class Primitive: public GeometricObject{
public:
    Matrix matrix, inverse;
    CSGPrimitiveNode *parent;
    CSGObject *csg;

    virtual void transformRay(Ray &ray);
    virtual void transformBoundingBox(const BoundingBox &box, Point &p, double &r);

public:
    Primitive(int _layer = 0): GeometricObject(_layer),
        matrix(Matrix()), inverse(Matrix()), parent(0), csg(0){}

    virtual void translate(double dx, double dy, double dz);
    virtual void rotate(double ang, double ax, double ay, double az);
    virtual void scale(double sx, double sy, double sz);
    virtual void scale(double s);
    virtual void shear(double dx, double dy, double dz, double sx, double sy, double sz);

    virtual bool hit(Ray ray) = 0;
    virtual bool hit(Ray ray, HitPoint &hitPoint) = 0;
    virtual bool hit(Ray ray, vector<HitPoint> &hitList) = 0;

    virtual BoundingBox baseBoundingBox() = 0;
    virtual void generateBoundingBox();

    friend class CSGObject;
};
