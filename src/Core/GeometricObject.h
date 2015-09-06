#pragma once

#include "Utility/Arrays.h"
#include "Utility/BoundingBox.h"
#include "Core/Ray.h"
#include "Core/HitPoint.h"
#include "Core/HitInfo.h"
#include "Core/Material.h"
#include <vector>

#define HIT_ROUTINE                                                       \
    if (ray.timeStamp <= timeStamp)                                       \
        return false;                                                     \
    transformRay(ray);

using std::vector;

class GeometricObject{
public:
    BoundingBox bBox;
    Material *material;
    int layer, id;
    long long timeStamp;

    static int objectCount;

    virtual void transformRay(Ray &ray){}

    enum BoundingBoxState{
        Outside = 0, OnBorder = 1, Inside = 2
    };

    GeometricObject(int _layer = 0):
        id(objectCount++), timeStamp(-1), layer(_layer){}

    virtual void translate(double dx, double dy, double dz) = 0;
    virtual void rotate(double ang, double ax, double ay, double az) = 0;
    virtual void scale(double sx, double sy, double sz) = 0;
    virtual void shear(double dx, double dy, double dz, double sx, double sy, double sz) = 0;

    virtual bool hit(Ray ray) = 0;
    virtual bool hit(Ray ray, HitPoint &hitPoint) = 0;

    virtual void getHitInfo(HitInfo &info){};

    virtual BoundingBox boundingBox(){return bBox;}
    virtual void generateBoundingBox() = 0;
    virtual int checkBoundingBox(const BoundingBox &box) = 0;

    static int count();
    static void resetCount();
};
