#include "Core/Mapping.h"

void BumpMapping::applyBumpMapping(HitInfo &info) const{
    pair<double, double> val = value(info);
    Vector du = info.du / info.du.squaredNorm();
    Vector dv = info.dv / info.dv.squaredNorm();
    if ((info.hitType == HitPoint::HitIn) || (info.hitType == HitPoint::HitInOut))
        info.shadeNormal = (info.shadeNormal + du * val.first + dv * val.second).normalized();
    else
        info.shadeNormal = (info.shadeNormal - du * val.first - dv * val.second).normalized();
}
