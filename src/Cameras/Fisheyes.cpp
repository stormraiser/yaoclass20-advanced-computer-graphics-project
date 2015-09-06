#include "Cameras/Fisheyes.h"
#include "Utility/def.h"
#include <cmath>

bool EquidistantFisheye::getAngle(double r, double &ang){
    if ((r < 0) || (r > PI))
        return false;
    ang = r;
    return true;
}

bool StereographicFisheye::getAngle(double r, double &ang){
    if (r < 0)
        return false;
    ang = 2 * atan(r * 0.5);
    return true;
}

bool EqualAreaFisheye::getAngle(double r, double &ang){
    if ((r < 0) || (r > 2))
        return false;
    ang = 2 * asin(r * 0.5);
    return true;
}

bool OrthographicFisheye::getAngle(double r, double &ang){
    if ((r < 0) || (r > 1))
        return false;
    ang = asin(r);
    return true;
}
