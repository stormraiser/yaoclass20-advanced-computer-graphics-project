#include "Mappings/SphereExpMapping.h"
#include <cmath>
#include "Utility/def.h"
#include <cstdio>

double SphereExpMapping::value(const HitInfo &info) const{
    int t = 2 * k * (log(tan(info.v * PI / 2)) / (c * 2 * PI) - info.u);
    while (t < 0)
        t += 2 * k;
    return t % 2;
}
