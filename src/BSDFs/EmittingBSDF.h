#pragma once

#include "Core/BSDF.h"

class EmittingBSDF: public BSDF{
private:
    RGBColor color;

public:
    EmittingBSDF(RGBColor _color):
        color(_color){}
    bool emit(HitInfo &info) const;
};
