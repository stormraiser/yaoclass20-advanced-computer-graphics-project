#include "Primitives/Cylinder.h"
#include <cmath>
#include <cstdio>

Cylinder::Cylinder(double cx, double cy, double cz, double r, double h, int _layer): Cylinder(_layer){
    scale(r, r, h / 2);
    translate(cx, cy, cz);
}

bool Cylinder::hit(Ray ray){
    HIT_ROUTINE
    Vector pd(ray.d.x, ray.d.y, 0), po(ray.o.x, ray.o.y, 0);
    double ld = pd.norm();
    double dis = pd * (-po) / ld;
    double r2 = po.squaredNorm() - dis * dis;
    if (r2 > 1)
        return false;
    double d = sqrt(1 - r2);
    double t1 = (dis - d) / ld;
    double t2 = (dis + d) / ld;
    double z1 = ray.o.z + ray.d.z * t1;
    double z2 = ray.o.z + ray.d.z * t2;
    if (ray.d.z > 0){
        if ((z1 > 1) || (z2 < -1))
            return false;
        if (z1 < -1)
            t1 = (-1 - ray.o.z) / ray.d.z;
        if (t1 > ray.tMax)
            return false;
        if (t1 > ray.tMin)
            return true;
        if (z2 > 1)
            t2 = (1 - ray.o.z) / ray.d.z;
        if ((t2 < ray.tMin) || (t2 > ray.tMax))
            return false;
        return true;
    }
    else{
        if ((z1 < -1) || (z2 > 1))
            return false;
        if (z1 > 1)
            t1 = (1 - ray.o.z) / ray.d.z;
        if (t1 > ray.tMax)
            return false;
        if (t1 > ray.tMin)
            return true;
        if (z2 < -1)
            t2 = (-1 - ray.o.z) / ray.d.z;
        if ((t2 < ray.tMin) || (t2 > ray.tMax))
            return false;
        return true;
    }
}

bool Cylinder::hit(Ray ray, HitPoint &hitPoint){
    HIT_ROUTINE
    Vector pd(ray.d.x, ray.d.y, 0), po(ray.o.x, ray.o.y, 0);
    double ld = pd.norm();
    double dis = pd * (-po) / ld;
    double r2 = po.squaredNorm() - dis * dis;
    if (r2 > 1)
        return false;
    double d = sqrt(1 - r2);
    double t1 = (dis - d) / ld;
    double t2 = (dis + d) / ld;
    double z1 = ray.o.z + ray.d.z * t1;
    double z2 = ray.o.z + ray.d.z * t2;
    int tag1 = 1;
    int tag2 = -1;
    if (ray.d.z > 0){
        if ((z1 > 1) || (z2 < -1))
            return false;
        if (z1 < -1){
            t1 = (-1 - ray.o.z) / ray.d.z;
            tag1 = 3;
        }
        if (t1 > ray.tMax)
            return false;
        if (t1 > ray.tMin){
            hitPoint.set(t1, tag1, HitPoint::HitIn, this);
            return true;
        }
        if (z2 > 1){
            t2 = (1 - ray.o.z) / ray.d.z;
            tag2 = -2;
        }
        if ((t2 < ray.tMin) || (t2 > ray.tMax))
            return false;
        hitPoint.set(t2, tag2, HitPoint::HitOut, this);
        return true;
    }
    else{
        if ((z1 < -1) || (z2 > 1))
            return false;
        if (z1 > 1){
            t1 = (1 - ray.o.z) / ray.d.z;
            tag1 = 2;
        }
        if (t1 > ray.tMax)
            return false;
        if (t1 > ray.tMin){
            hitPoint.set(t1, tag1, HitPoint::HitIn, this);
            return true;
        }
        if (z2 < -1){
            t2 = (-1 - ray.o.z) / ray.d.z;
            tag2 = -3;
        }
        if ((t2 < ray.tMin) || (t2 > ray.tMax))
            return false;
        hitPoint.set(t2, tag2, HitPoint::HitOut, this);
        return true;
    }
}

bool Cylinder::hit(Ray ray, vector<HitPoint> &hitList){
    HIT_ROUTINE
    Vector pd(ray.d.x, ray.d.y, 0), po(ray.o.x, ray.o.y, 0);
    double ld = pd.norm();
    double dis = pd * (-po) / ld;
    double r2 = po.squaredNorm() - dis * dis;
    if (r2 > 1)
        return false;
    double d = sqrt(1 - r2);
    double t1 = (dis - d) / ld;
    double t2 = (dis + d) / ld;
    double z1 = ray.o.z + ray.d.z * t1;
    double z2 = ray.o.z + ray.d.z * t2;
    int tag1 = 1;
    int tag2 = -1;
    if (ray.d.z > 0){
        if ((z1 > 1) || (z2 < -1))
            return false;
        if (z1 < -1){
            t1 = (-1 - ray.o.z) / ray.d.z;
            tag1 = 3;
        }
        hitList.push_back(HitPoint(t1, tag1, HitPoint::HitIn, this));
        if (z2 > 1){
            t2 = (1 - ray.o.z) / ray.d.z;
            tag2 = -2;
        }
        hitList.push_back(HitPoint(t2, tag2, HitPoint::HitOut, this));
        return true;
    }
    else{
        if ((z1 < -1) || (z2 > 1))
            return false;
        if (z1 > 1){
            t1 = (1 - ray.o.z) / ray.d.z;
            tag1 = 2;
        }
        hitList.push_back(HitPoint(t1, tag1, HitPoint::HitIn, this));
        if (z2 < -1){
            t2 = (-1 - ray.o.z) / ray.d.z;
            tag2 = -3;
        }
        hitList.push_back(HitPoint(t2, tag2, HitPoint::HitOut, this));
        return true;
    }
}

void Cylinder::getHitInfo(HitInfo &info){
    info.hitPoint = info.ray.o + info.ray.d * info.t;
    info.localPoint = inverse.operatedPoint(info.hitPoint);
    Vector vt = Vector(info.localPoint.x, info.localPoint.y, 0);
    //if ((info.tag > 3) || (info.tag < -3))
    //    printf("%d>\n", info.tag);
    switch(info.tag){
        case 1:
        case -1:
            info.face = 0;
            info.v = info.localPoint.z * 0.5 + 0.5;
            info.u = atan2(info.localPoint.y, info.localPoint.x) * INVPI * 0.5 + 0.5;
            info.du = Vector(-info.localPoint.y, info.localPoint.x, 0) * PI * 2;
            info.dv = Vector(0, 0, 1);
            if (info.tag > 0)
                info.shadeNormal = info.normal = vt;
            else
                info.shadeNormal = info.normal = -vt;
            break;
        case 2:
        case -2:
            info.face = 1;
            info.v = 1 - vt.norm();
            info.u = atan2(info.localPoint.y, info.localPoint.x) * INVPI * 0.5 + 0.5;
            info.du = Vector(-info.localPoint.y, info.localPoint.x, 0) * PI * 2;
            info.dv = -vt.normalized();
            if (info.tag > 0)
                info.shadeNormal = info.normal = Vector(0, 0, 1);
            else
                info.shadeNormal = info.normal = Vector(0, 0, -1);
            break;
        case 3:
        case -3:
            info.face = 2;
            info.v = 1 - vt.norm();
            info.u = 0.5 - atan2(info.localPoint.y, info.localPoint.x) * INVPI * 0.5;
            info.du = Vector(info.localPoint.y, -info.localPoint.x, 0) * PI * 2;
            info.dv = -vt.normalized();
            if (info.tag > 0)
                info.shadeNormal = info.normal = Vector(0, 0, -1);
            else
                info.shadeNormal = info.normal = Vector(0, 0, 1);
            break;
    }
    inverse.operateNormal(info.normal);
    inverse.operateNormal(info.shadeNormal);
    inverse.operateVector(info.du);
    inverse.operateVector(info.dv);
}

int Cylinder::checkBoundingBox(const BoundingBox &box){
    CHECK_ROUTINE
    double dt = Vector(p.x, p.y, 0).norm();
    if ((dt + r <= 1) && (fabs(p.z) + r <= 1))
        return Inside;
    if ((dt - r >= 1) || (fabs(p.z) - r >= 1))
        return Outside;
    return OnBorder;
}
