#pragma once

#include "Core/BSDF.h"
#include "Core/Mapping.h"

#define GLOSSY_THRESHOD 10

class PhongBSDF: public BSDF{
private:
    double e;
    RGBColor color;
    Texture *texture;
    BumpMapping *bump;

public:
    PhongBSDF(double _e, RGBColor _color = 1, Texture *_texture = 0, BumpMapping *_bump = 0):
        e(_e), color(_color), texture(_texture), bump(_bump){}

    bool f(HitInfo &info) const;
    bool diffuseF(HitInfo &info) const
        {return e <= GLOSSY_THRESHOD ? f(info) : false;}
    bool diffuseGlossyF(HitInfo &info) const
        {return f(info);}

    bool s(HitInfo &info) const;
    bool specularGlossyS(HitInfo &info) const
        {return e > GLOSSY_THRESHOD ? s(info) : false;}

    bool hasDiffuseComponent() const
        {return e <= GLOSSY_THRESHOD;}
};
