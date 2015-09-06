#pragma once

#include "Core/BSDF.h"
#include "Core/Mapping.h"

class LambertianBSDF: public BSDF{
private:
    RGBColor color;
    Texture *texture;
    BumpMapping *bump;

public:
    LambertianBSDF(RGBColor _color = 1, Texture *_texture = 0, BumpMapping *_bump = 0):
        color(_color), texture(_texture), bump(_bump){}

    bool f(HitInfo &info) const;
    bool diffuseF(HitInfo &info) const
        {return f(info);}
    bool diffuseGlossyF(HitInfo &info) const
        {return f(info);}

    bool s(HitInfo &info) const;

    bool hasDiffuseComponent() const
        {return true;}
};
