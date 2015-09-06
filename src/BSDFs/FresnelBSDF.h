#pragma once

#include <cstdio>
#include "Core/BSDF.h"
#include "Core/Mapping.h"

class FresnelBSDF: public BSDF{
private:
    BumpMapping *bump;

public:
    FresnelBSDF(BumpMapping *_bump = 0): bump(_bump){}

    bool s(HitInfo &info) const;
    bool specularS(HitInfo &info) const {return s(info);}
    bool specularGlossyS(HitInfo &info) const {return s(info);}

    bool ms(HitInfo &info) const;
    bool specularMS(HitInfo &info) const {return ms(info);}
    bool specularGlossyMS(HitInfo &info) const {return ms(info);}
};
