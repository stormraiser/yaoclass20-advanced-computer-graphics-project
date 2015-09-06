#pragma once

#include <cstdio>
#include "Core/HitInfo.h"

#define REGULATE_WI_REFLECT(vec)                                                                              \
    if (vec * info.normal < 0.01)                                                                             \
        vec = (vec - (vec * info.normal) * info.normal).normalized() * 0.9999499987 + info.normal * 0.01;

#define REGULATE_WI_NOREFLECT(vec)                                                                            \
    if (vec * info.normal > 0.01)                                                                             \
        vec = (vec - (vec * info.normal) * info.normal).normalized() * 0.9999499987 - info.normal * 0.01;


class BSDF{
public:
    virtual bool f(HitInfo &info) const {return false;}
    virtual bool diffuseF(HitInfo &info) const {return false;}
    virtual bool diffuseGlossyF(HitInfo &info) const {return false;}

    virtual bool s(HitInfo &info) const {return false;}
    virtual bool specularS(HitInfo &info) const {return false;}
    virtual bool specularGlossyS(HitInfo &info) const {return false;}

    virtual bool ms(HitInfo &info) const
        {info.hasSecondary = false; return s(info);}
    virtual bool specularMS(HitInfo &info) const
        {info.hasSecondary = false; return specularS(info);}
    virtual bool specularGlossyMS(HitInfo &info) const
        {info.hasSecondary = false; return specularGlossyS(info);}

    virtual bool emit(HitInfo &info) const {return false;}

    virtual bool hasDiffuseComponent() const {return false;}
};
