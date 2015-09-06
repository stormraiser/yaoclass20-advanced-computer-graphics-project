#include "BSDFs/PhongBSDF.h"
#include "Utility/func.h"

bool PhongBSDF::f(HitInfo &info) const{
    if (bump != 0)
        bump->applyBumpMapping(info);
    double t = info.shadeNormal * info.wi;
    Vector r = -info.wi + 2 * info.shadeNormal * t;
    double t2 = r * info.wo;
    info.pdf = t * (info.shadeNormal * info.wi);
    info.isReflected = true;
    info.emitted = 0;
    if (t2 > 0)
        info.scattered = pow(t2, e) * color * (texture == 0 ? 1 : texture->value(info));
    else
        info.scattered = 0;
    return true;
}

bool PhongBSDF::s(HitInfo &info) const{
    if (bump != 0)
        bump->applyBumpMapping(info);
    Vector w = -info.wo + 2.0 * info.shadeNormal * (info.shadeNormal * info.wo);
    Vector u = w ^ info.shadeNormal;
    u.normalize();
    Vector v = w ^ u;
    double pu, pv, pw;

    do{
        double sx = randReal();
        double sy = randReal();
        mapToHemisphere(sx, sy, pu, pv, pw, e);
        info.wi = pu * u + pv * v + pw * w;
    } while (info.shadeNormal * info.wi < 0);
    double t = pow(w * info.wi, e);
    info.pdf = t * (info.shadeNormal * info.wi);
    info.isReflected = true;
    info.emitted = 0;
    info.scattered = t * color * (texture == 0 ? 1 : texture->value(info));
    info.type = e > GLOSSY_THRESHOD ? HitInfo::Glossy : HitInfo::Diffuse;
    return true;
}
