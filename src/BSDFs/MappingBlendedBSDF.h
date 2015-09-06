#pragma once

#include "Core/BSDF.h"
#include "Core/Mapping.h"
#include <cstdio>

class MappingBlendedBSDF: public BSDF{
private:
    BSDF *bsdf1, *bsdf2;
    Mapping *mapping;

public:
    MappingBlendedBSDF(BSDF *_bsdf1, BSDF *_bsdf2, Mapping *_mapping):
        bsdf1(_bsdf1), bsdf2(_bsdf2), mapping(_mapping){}

    bool f(HitInfo &info) const;
    bool diffuseF(HitInfo &info) const;
    bool diffuseGlossyF(HitInfo &info) const;

    bool s(HitInfo &info) const;
    bool specularS(HitInfo &info) const;
    bool specularGlossyS(HitInfo &info) const;

    bool hasDiffuseComponent() const
        {return bsdf1->hasDiffuseComponent() || bsdf2->hasDiffuseComponent();}
};
