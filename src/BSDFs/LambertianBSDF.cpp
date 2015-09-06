#include "BSDFs/LambertianBSDF.h"
#include "Utility/func.h"

bool LambertianBSDF::f(HitInfo &info) const{
    if (bump != 0)
        bump->applyBumpMapping(info);
    if (info.shadeNormal * info.wi > 0)
        info.scattered = color * (texture == 0 ? 1 : texture->value(info)) / (info.shadeNormal * info.wi);
    else
        info.scattered = 0;
    return true;
}

bool LambertianBSDF::s(HitInfo &info) const{
    if (bump != 0)
        bump->applyBumpMapping(info);
    Vector w = info.shadeNormal;
    Vector u = (info.wo ^ w).normalized();
    Vector v = (w ^ u).normalized();
    double pu, pv, pw;
    mapToHemisphere(randReal(), randReal(), pu, pv, pw);
    info.wi = u * pu + v * pv + w * pw;
    REGULATE_WI_REFLECT(info.wi)
    //info.pdf = t * (info.shadeNormal * info.wi);
    info.isReflected = true;
    info.emitted = 0;
    info.scattered = color * (texture == 0 ? 1 : texture->value(info)) / (info.shadeNormal * info.wi);
    info.type = HitInfo::Diffuse;
    return true;
}
