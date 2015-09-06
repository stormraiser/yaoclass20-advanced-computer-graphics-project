#pragma once

#include "Core/BSDF.h"
#include "Core/Mapping.h"

class PhaseIsotropic: public BSDF{
private:
    RGBColor color;
    Texture *texture;

public:
    PhaseIsotropic(RGBColor _color = 1, Texture *_texture = 0): color(_color), texture(_texture){}
    bool f(HitInfo &info) const;
    bool s(HitInfo &info) const;
};
