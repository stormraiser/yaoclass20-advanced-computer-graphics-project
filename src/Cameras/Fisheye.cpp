#include "Cameras/Fisheye.h"

#include <cstdio>

bool Fisheye::shootRay(double x, double y, Ray &ray){
    double ang;
    double r = sqrt(x * x + y * y);
    if (!getAngle(r, ang))
        return false;
    Vector dir, adx, ady;
    double ax = 0, ay = 0;
    //
    if (r != 0){
        x /= r;
        y /= r;
        dir = lookDir * cos(ang) + (x * rightDir + y * upDir) * sin(ang);
        adx = y * rightDir - x * upDir;
        ady = adx ^ dir;
    }
    else{
        dir = lookDir;
        adx = rightDir;
        ady = upDir;
    }
    Point focusPoint = pos + dir * focalDis;
    ray.o = pos + ax * aperture * adx + ay * aperture * ady;
    ray.d = (focusPoint - ray.o).normalized();
    return true;
}
