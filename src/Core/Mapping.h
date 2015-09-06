#pragma once

#include <utility>
#include "Core/HitInfo.h"
#include "Utility/Arrays.h"

using namespace std;

template <typename ValType> class MappingBase{
public:
    virtual ValType value(const HitInfo &info) const = 0;
};

class BumpMapping: public MappingBase<pair<double, double> >{
public:
    void applyBumpMapping(HitInfo &info) const;
};

typedef MappingBase<RGBColor> Texture;
typedef MappingBase<double> Mapping;
