#pragma once

#include "Core/BSDF.h"
#include "Core/Mapping.h"

class SpecularBSDF: public BSDF{
private:
    RGBColor color;
    Texture *texture;
    BumpMapping *bump;

public:
    SpecularBSDF(RGBColor _color = 1, Texture *_texture = 0, BumpMapping *_bump = 0): color(_color), texture(_texture), bump(_bump){}
    bool s(HitInfo &info) const;
    bool specularS(HitInfo &info) const {return s(info);}
    bool specularGlossyS(HitInfo &info) const {return s(info);}
};
