#include "BSDFs/PhaseIsotropic.h"
#include "Utility/func.h"
#include "Utility/def.h"
#include <cstdlib>

bool PhaseIsotropic::f(HitInfo &info) const{
    info.emitted = 0;
    info.scattered = 1 / (PI * 4) * color * (texture == 0 ? 1 : texture->value(info));
    return true;
}

bool PhaseIsotropic::s(HitInfo &info) const{
    double pu, pv, pw;
    mapToHemisphere(randReal(), randReal(), pu, pv, pw, 0);
    info.wi = Vector(pu, pv, pw);
    if (rand() % 2 == 0)
        info.wi = -info.wi;
    info.emitted = 0;
    info.scattered = color * (texture == 0 ? 1 : texture->value(info));
    return true;
}

