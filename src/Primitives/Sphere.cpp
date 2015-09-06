#include "Primitives/Sphere.h"

#include <cstdio>

Sphere::Sphere(double cx, double cy, double cz, double r, int _layer): Sphere(_layer){
    scale(r);
    translate(cx, cy, cz);
}

bool Sphere::hit(Ray ray){
    HIT_ROUTINE
    double dis = ray.d * (-ray.o) / ray.d.norm();
    double r2 = ray.o.squaredNorm() - dis * dis;
    if (r2 > 1)
        return false;
    double d = sqrt(1 - r2);
    double t = (dis - d) / ray.d.norm();
    if (t > ray.tMax)
        return false;
    if (t > ray.tMin)
        return true;
    t = (dis + d) / ray.d.norm();
    if ((t > ray.tMin) && (t < ray.tMax))
        return true;
    return false;
}

bool Sphere::hit(Ray ray, HitPoint &hitPoint){
    HIT_ROUTINE
    double dis = ray.d * (-ray.o) / ray.d.norm();
    double r2 = ray.o.squaredNorm() - dis * dis;
    //printf("%lf %lf\n", dis, r2);
    if (r2 > 1)
        return false;
    double d = sqrt(1 - r2);
    double t = (dis - d) / ray.d.norm();
    if (t > ray.tMax)
        return false;
    if (t > ray.tMin){
        hitPoint.set(t, 1, HitPoint::HitIn, this);
        return true;
    }
    t = (dis + d) / ray.d.norm();
    if ((t > ray.tMin) && (t < ray.tMax)){
        hitPoint.set(t, -1, HitPoint::HitOut, this);
        return true;
    }
    return false;
}

bool Sphere::hit(Ray ray, vector<HitPoint> &hitList){
    HIT_ROUTINE
    double dis = ray.d * (-ray.o) / ray.d.norm();
    double r2 = ray.o.squaredNorm() - dis * dis;
    if (r2 > 1)
        return false;
    double d = sqrt(1 - r2);
    double t = (dis - d) / ray.d.norm();
    hitList.push_back(HitPoint(t, 1, HitPoint::HitIn, this));
    t = (dis + d) / ray.d.norm();
    hitList.push_back(HitPoint(t, -1, HitPoint::HitOut, this));
    return true;
}

int Sphere::checkBoundingBox(const BoundingBox &box){
    CHECK_ROUTINE
    if (p.norm() + r <= 1)
        return Inside;
    if (p.norm() - r >= 1)
        return Outside;
    return OnBorder;
}

void Sphere::getHitInfo(HitInfo &info){
    info.hitPoint = info.ray.o + info.ray.d * info.t;
    info.localPoint = inverse.operatedPoint(info.hitPoint);
    info.face = 0;
    if (info.tag == 1)
        info.shadeNormal = info.normal = info.localPoint;
    else
        info.shadeNormal = info.normal = -info.localPoint;
    info.u = atan2(info.localPoint.y, info.localPoint.x) * INVPI * 0.5 + 0.5;
    info.v = asin(info.localPoint.z) * INVPI + 0.5;
    info.du = Vector(-info.localPoint.y, info.localPoint.x, 0) * PI * 2;
    double t = sqrt(1 - info.localPoint.z * info.localPoint.z);
    info.dv = Vector(info.localPoint.z * info.localPoint.x / t, info.localPoint.z * info.localPoint.y / t, t) * PI;
    inverse.operateNormal(info.normal);
    inverse.operateNormal(info.shadeNormal);
    inverse.operateVector(info.du);
    inverse.operateVector(info.dv);
}
