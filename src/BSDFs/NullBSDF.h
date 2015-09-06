#pragma once

#include "Core/BSDF.h"

class NullBSDF: public BSDF{
public:
    bool s(HitInfo &info) const;
    bool specularS(HitInfo &info) const {return s(info);}
    bool specularGlossyS(HitInfo &info) const {return s(info);}
};
