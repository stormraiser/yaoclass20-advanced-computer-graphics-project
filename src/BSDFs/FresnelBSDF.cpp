#include "BSDFs/FresnelBSDF.h"
#include "Utility/func.h"
#include <cmath>

bool FresnelBSDF::s(HitInfo &info) const{
    double ct, st, p;
    double t = info.shadeNormal * info.wo;
    if (bump != 0)
        bump->applyBumpMapping(info);
    p = fresnel(info.n1, info.n2, t, ct, st);
    //printf("* %f %f %f %f %f %f\n", info.n1, info.n2, t, ct, st, p);
    if (randReal() < p){
        info.wi = -info.wo + 2 * t * info.shadeNormal;
        REGULATE_WI_REFLECT(info.wi)
        info.isReflected = true;
    }
    else{
        Vector v = (-info.wo + t * info.shadeNormal).normalized();
        info.wi = v * st - info.shadeNormal * ct;
        REGULATE_WI_NOREFLECT(info.wi)
        info.isReflected = false;
    }
    info.type = HitInfo::Specular;
    info.pdf = 1;
    info.emitted = 0;
    info.scattered = 1 / fabs(info.shadeNormal * info.wi);
    return true;
}

bool FresnelBSDF::ms(HitInfo &info) const{
    double ct, st, p;
    double t = info.shadeNormal * info.wo;
    if (bump != 0)
        bump->applyBumpMapping(info);
    p = fresnel(info.n1, info.n2, t, ct, st);

    //
    //p = 0;
    //printf("%f\n", p);

    info.wi = -info.wo + 2 * t * info.shadeNormal;
    REGULATE_WI_REFLECT(info.wi)
    info.isReflected = true;
    info.scattered = 1 / fabs(info.shadeNormal * info.wi) * p;

    if (p != 1){
        Vector v = (-info.wo + t * info.shadeNormal).normalized();
        info.wi2 = v * st - info.shadeNormal * ct;
        REGULATE_WI_NOREFLECT(info.wi2)
        info.isReflected2 = false;
        info.scattered2 = 1 / fabs(info.shadeNormal * info.wi2) * (1 - p);

        info.hasSecondary = true;
    }
    else
        info.hasSecondary = false;

    info.type = info.type2 = HitInfo::Specular;
    info.pdf = 1;
    info.emitted = 0;
    return true;
}
