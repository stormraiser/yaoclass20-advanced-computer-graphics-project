#include "BSDFs/SpecularBSDF.h"

bool SpecularBSDF::s(HitInfo &info) const{
    if (bump != 0)
        bump->applyBumpMapping(info);
    info.wi = -info.wo + 2.0 * info.shadeNormal * (info.shadeNormal * info.wo);
    REGULATE_WI_REFLECT(info.wi)
    info.isReflected = true;
    info.pdf = 1;
    info.emitted = 0;
    info.scattered = 1 / (info.shadeNormal * info.wi) * color * (texture == 0 ? 1 : texture->value(info));
    info.type = HitInfo::Specular;
    return true;
}
