#include "Panoramics.h"
#include "Utility/def.h"
#include <cmath>

bool EquirectangularPanoramic::getAngle(double r, double &ang){
    if ((r < -PI * 0.5) || (r > PI * 0.5))
        return false;
    ang = r;
    return true;
}

bool MercatorPanoramic::getAngle(double r, double &ang){
    ang = atan(r);
    return true;
}

bool BraunPanoramic::getAngle(double r, double &ang){
    if ((r < -2) || (r > 2))
        return false;
    ang = 2 * atan(r * 0.5);
    return true;
}

bool CylindricalEqualAreaPanoramic::getAngle(double r, double &ang){
    if ((r < -1) || (r > 1))
        return false;
    ang = asin(r);
    return true;
}
