#include "Primitives/LightSquare.h"
#include <cmath>

#include <cstdio>

bool LightSquare::hit(Ray ray){
    HIT_ROUTINE
    double t = (ray.o - pos) * dir / (ray.d * -dir / ray.d.norm());
    if ((t < ray.tMin) || (t > ray.tMax))
        return false;
    Vector pt = ray.o + ray.d * t - pos;
    return ((fabs(pt * up * 2) < h) && (fabs(pt * right * 2) < w));
}

bool LightSquare::hit(Ray ray, HitPoint &hitPoint){
    HIT_ROUTINE
    double t = (pos - ray.o) * dir / (ray.d * dir);
    if ((t < ray.tMin) || (t > ray.tMax))
        return false;
    Vector pt = ray.o + ray.d * t - pos;
    if ((fabs(pt * up * 2) > h) || (fabs(pt * right * 2) > w))
        return false;
    if (ray.d * dir < 0)
        hitPoint.set(t, 1, HitPoint::HitInOut, this);
    else
        hitPoint.set(t, -1, HitPoint::HitInOut, this);
    return true;
}

bool LightSquare::hit(Ray ray, vector<HitPoint> &hitList){
    return false;
}

int LightSquare::checkBoundingBox(const BoundingBox &box){
    return Outside;
}

void LightSquare::getHitInfo(HitInfo &info){
    info.hitPoint = info.ray.o + info.ray.d * info.t;
    info.localPoint = inverse.operatedPoint(info.hitPoint);
    if (info.tag == 1){
        info.face = 0;
        info.shadeNormal = info.normal = dir;
    }
    else{
        info.face = 1;
        info.shadeNormal = info.normal = -dir;
    }
    info.u = (info.hitPoint - pos) * right / w + 0.5;
    info.v = (info.hitPoint - pos) * up / h + 0.5;
    inverse.operateNormal(info.normal);
    inverse.operateNormal(info.shadeNormal);
}
