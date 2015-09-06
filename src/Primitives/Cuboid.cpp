#include "Primitives/Cuboid.h"
#include "Utility/def.h"

Cuboid::Cuboid(double cx, double cy, double cz, double lx, double ly, double lz, int _layer): Cuboid(_layer){
    scale(lx * 0.5, ly * 0.5, lz * 0.5);
    translate(cx, cy, cz);
}

bool Cuboid::solve(const Ray &ray, double &inMax, double &outMin, int &inTag, int &outTag){
    double t[7];
    inMax = -INF;
    outMin = INF;
    t[1] = (-1 - ray.o.x) / ray.d.x;
    t[2] = (1 - ray.o.x) / ray.d.x;
    t[3] = (-1 - ray.o.y) / ray.d.y;
    t[4] = (1 - ray.o.y) / ray.d.y;
    t[5] = (-1 - ray.o.z) / ray.d.z;
    t[6] = (1 - ray.o.z) / ray.d.z;
    if (ray.d.x > 0){
        if (t[1] > inMax){
            inMax = t[1];
            inTag = 1;
        }
        if (t[2] < outMin){
            outMin = t[2];
            outTag = 2;
        }
    }
    else{
        if (t[1] < outMin){
            outMin = t[1];
            outTag = 1;
        }
        if (t[2] > inMax){
            inMax = t[2];
            inTag = 2;
        }
    }
    if (ray.d.y > 0){
        if (t[3] > inMax){
            inMax = t[3];
            inTag = 3;
        }
        if (t[4] < outMin){
            outMin = t[4];
            outTag = 4;
        }
    }
    else{
        if (t[3] < outMin){
            outMin = t[3];
            outTag = 3;
        }
        if (t[4] > inMax){
            inMax = t[4];
            inTag = 4;
        }
    }
    if (ray.d.z > 0){
        if (t[5] > inMax){
            inMax = t[5];
            inTag = 5;
        }
        if (t[6] < outMin){
            outMin = t[6];
            outTag = 6;
        }
    }
    else{
        if (t[5] < outMin){
            outMin = t[5];
            outTag = 5;
        }
        if (t[6] > inMax){
            inMax = t[6];
            inTag = 6;
        }
    }
    return inMax < outMin;
}

bool Cuboid::solve(const Ray &ray){
    double t[7], inMax, outMin;
    inMax = -INF;
    outMin = INF;
    t[1] = (-1 - ray.o.x) / ray.d.x;
    t[2] = (1 - ray.o.x) / ray.d.x;
    t[3] = (-1 - ray.o.y) / ray.d.y;
    t[4] = (1 - ray.o.y) / ray.d.y;
    t[5] = (-1 - ray.o.z) / ray.d.z;
    t[6] = (1 - ray.o.z) / ray.d.z;
    if (ray.d.x > 0){
        if (t[1] > inMax)
            inMax = t[1];
        if (t[2] < outMin)
            outMin = t[2];
    }
    else{
        if (t[1] < outMin)
            outMin = t[1];
        if (t[2] > inMax)
            inMax = t[2];
    }
    if (ray.d.y > 0){
        if (t[3] > inMax)
            inMax = t[3];
        if (t[4] < outMin)
            outMin = t[4];
    }
    else{
        if (t[3] < outMin)
            outMin = t[3];
        if (t[4] > inMax)
            inMax = t[4];
    }
    if (ray.d.z > 0){
        if (t[5] > inMax)
            inMax = t[5];
        if (t[6] < outMin)
            outMin = t[6];
    }
    else{
        if (t[5] < outMin)
            outMin = t[5];
        if (t[6] > inMax)
            inMax = t[6];
    }
    return inMax < outMin;
}

bool Cuboid::hit(Ray ray){
    HIT_ROUTINE
    double tIn, tOut;
    int inTag, outTag;
    if (!solve(ray, tIn, tOut, inTag, outTag))
        return false;
    if ((tIn > ray.tMax) || (tOut < ray.tMin))
        return false;
    else
        return true;
}

bool Cuboid::hit(Ray ray, HitPoint &hitPoint){
    HIT_ROUTINE
    double tIn, tOut;
    int inTag, outTag;
    if (!solve(ray, tIn, tOut, inTag, outTag))
        return false;
    if ((tIn > ray.tMax) || (tOut < ray.tMin))
        return false;
    if (tIn > ray.tMin)
        hitPoint.set(tIn, inTag, HitPoint::HitIn, this);
    else
        hitPoint.set(tOut, -outTag, HitPoint::HitOut, this);
    return true;
}

bool Cuboid::hit(Ray ray, vector<HitPoint> &hitList){
    HIT_ROUTINE
    double tIn, tOut;
    int inTag, outTag;
    if (!solve(ray, tIn, tOut, inTag, outTag))
        return false;
    hitList.push_back(HitPoint(tIn, inTag, HitPoint::HitIn, this));
    hitList.push_back(HitPoint(tOut, -outTag, HitPoint::HitOut, this));
    return true;
}

void Cuboid::getHitInfo(HitInfo &info){
    info.hitPoint = info.ray.o + info.ray.d * info.t;
    info.localPoint = inverse.operatedPoint(info.hitPoint);
    switch(info.tag){
        case 1:
        case -1:
            info.face = 0;
            info.u = -info.localPoint.y * 0.5 + 0.5;
            info.v = info.localPoint.z * 0.5 + 0.5;
            info.du = Vector(0, -1, 0);
            info.dv = Vector(0, 0, 1);
            if (info.tag > 0)
                info.shadeNormal = info.normal = Normal(-1, 0, 0);
            else
                info.shadeNormal = info.normal = Normal(1, 0, 0);
            break;
        case 2:
        case -2:
            info.face = 2;
            info.u = info.localPoint.y * 0.5 + 0.5;
            info.v = info.localPoint.z * 0.5 + 0.5;
            info.du = Vector(0, 1, 0);
            info.dv = Vector(0, 0, 1);
            if (info.tag > 0)
                info.shadeNormal = info.normal = Normal(1, 0, 0);
            else
                info.shadeNormal = info.normal = Normal(-1, 0, 0);
            break;
        case 3:
        case -3:
            info.face = 1;
            info.u = info.localPoint.x * 0.5 + 0.5;
            info.v = info.localPoint.z * 0.5 + 0.5;
            info.du = Vector(1, 0, 0);
            info.dv = Vector(0, 0, 1);
            if (info.tag > 0)
                info.shadeNormal = info.normal = Normal(0, -1, 0);
            else
                info.shadeNormal = info.normal = Normal(0, 1, 0);
            break;
        case 4:
        case -4:
            info.face = 3;
            info.u = -info.localPoint.x * 0.5 + 0.5;
            info.v = info.localPoint.z * 0.5 + 0.5;
            info.du = Vector(-1, 0, 0);
            info.dv = Vector(0, 0, 1);
            if (info.tag > 0)
                info.shadeNormal = info.normal = Normal(0, 1, 0);
            else
                info.shadeNormal = info.normal = Normal(0, -1, 0);
            break;
        case 5:
        case -5:
            info.face = 5;
            info.u = -info.localPoint.x * 0.5 + 0.5;
            info.v = info.localPoint.y * 0.5 + 0.5;
            info.du = Vector(-1, 0, 0);
            info.dv = Vector(0, 1, 0);
            if (info.tag > 0)
                info.shadeNormal = info.normal = Normal(0, 0, -1);
            else
                info.shadeNormal = info.normal = Normal(0, 0, 1);
            break;
        case 6:
        case -6:
            info.face = 4;
            info.u = info.localPoint.x * 0.5 + 0.5;
            info.v = info.localPoint.y * 0.5 + 0.5;
            info.du = Vector(1, 0, 0);
            info.dv = Vector(0, 1, 0);
            if (info.tag > 0)
                info.shadeNormal = info.normal = Normal(0, 0, 1);
            else
                info.shadeNormal = info.normal = Normal(0, 0, -1);
            break;
    }
    inverse.operateNormal(info.normal);
    inverse.operateNormal(info.shadeNormal);
    inverse.operateVector(info.du);
    inverse.operateVector(info.dv);
}

int Cuboid::checkBoundingBox(const BoundingBox &box){
    CHECK_ROUTINE
    if ((p.x - r >= -1) && (p.x + r <= 1) && (p.y - r >= -1) && (p.y + r <= 1) && (p.z - r >= -1) && (p.z + r <= 1))
        return Inside;
    if ((p.x + r >= -1) && (p.x - r <= 1) && (p.y + r >= -1) && (p.y - r <= 1) && (p.z + r >= -1) && (p.z - r <= 1))
        return OnBorder;
    return Outside;
}
