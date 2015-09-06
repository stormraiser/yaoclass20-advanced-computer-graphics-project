#include "BSDFs/NullBSDF.h"
#include <cmath>

bool NullBSDF::s(HitInfo &info) const{
    info.wi = -info.wo;
    info.isReflected = false;
    info.type = HitInfo::Specular;
    info.pdf = 1;
    info.emitted = 0;
    info.scattered = 1 / fabs(info.shadeNormal * info.wi);
    return true;
}
