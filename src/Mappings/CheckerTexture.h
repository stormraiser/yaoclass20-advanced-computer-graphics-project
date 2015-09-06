#pragma once

#include "Core/Mapping.h"

class CheckerTexture: public Texture{
private:
    Texture *texture1, *texture2;
    double uScale, vScale, uOffset, vOffset;

public:
    CheckerTexture(Texture *_texture1, Texture *_texture2, double _uScale, double _vScale, double _uOffset, double _vOffset):
        texture1(_texture1), texture2(_texture2), uScale(_uScale), vScale(_vScale), uOffset(_uOffset), vOffset(_vOffset){}

    RGBColor value(const HitInfo &info) const;
};
