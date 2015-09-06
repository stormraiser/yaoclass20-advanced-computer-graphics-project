#pragma once

#include "Core/BSDF.h"

class FresnelBlendBSDF: public BSDF{
private:
    BSDF *bsdf1, *bsdf2;

public:
    FresnelBlendBSDF(BSDF *_bsdf1, BSDF *_bsdf2):
        bsdf1(_bsdf1), bsdf2(_bsdf2){}

    bool f(HitInfo &info) const;
    bool diffuseF(HitInfo &info) const;
    bool diffuseGlossyF(HitInfo &info) const;

    bool s(HitInfo &info) const;
    bool specularS(HitInfo &info) const;
    bool specularGlossyS(HitInfo &info) const;

    ///*
    bool ms(HitInfo &info) const;
    bool specularMS(HitInfo &info) const;
    bool specularGlossyMS(HitInfo &info) const;
    //*/

    bool hasDiffuseComponent() const
        {return bsdf1->hasDiffuseComponent() || bsdf2->hasDiffuseComponent();}
};
