#include "Cameras/Panoramic.h"
#include "Utility/def.h"

bool Panoramic::shootRay(double x, double y, Ray &ray){
    double ang;
    if ((x < -PI) || (x > PI) || (!getAngle(y, ang)))
        return false;
    double ax = 0, ay = 0;
    Vector dir = lookDir * cos(x) + rightDir * sin(x) + upDir * tan(ang);
    Vector adx = rightDir * cos(x) - lookDir * sin(x);
    Point focusPoint = pos + dir * focalDis;
    ray.o = pos + ax * aperture * adx + ay * aperture * upDir;
    ray.d = (focusPoint - ray.o).normalized();
    return true;
}
