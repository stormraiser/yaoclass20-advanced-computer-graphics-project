#pragma once

#include "Core/Mapping.h"

class SphereExpMapping: public Mapping{
private:
    double c;
    int k;

public:
    SphereExpMapping(double _c, int _k): c(_c), k(_k){}
    double value(const HitInfo &info) const;
};
