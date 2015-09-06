#pragma once

#include "Core/Mapping.h"

class PureColor: public Texture{
private:
    RGBColor color;

public:
    PureColor(RGBColor _color):
        color(_color){}
    RGBColor value(const HitInfo &info) const
        {return color;}
};
