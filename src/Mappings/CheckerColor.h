#pragma once

#include "Core/Mapping.h"

class CheckerColor: public Texture{
private:
    RGBColor color1, color2;
    double uScale, vScale, uOffset, vOffset;

public:
    CheckerColor(RGBColor _color1, RGBColor _color2, double _uScale, double _vScale, double _uOffset, double _vOffset):
        color1(_color1), color2(_color2), uScale(_uScale), vScale(_vScale), uOffset(_uOffset), vOffset(_vOffset){}

    RGBColor value(const HitInfo &info) const;
};
