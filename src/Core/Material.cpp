#include "Core/Material.h"
#include <cmath>

double Material::emitFilterFunc(double t, double l){
    if (t >= 0.9999)
        return l;
    else
        return (pow(t, l) - 1) / log(t);
}

RGBColor Material::emitFilter(double l){
    double r = emitFilterFunc(filterColor.r, l) * emitColor.r;
    double g = emitFilterFunc(filterColor.g, l) * emitColor.g;
    double b = emitFilterFunc(filterColor.b, l) * emitColor.b;
    return RGBColor(r, g, b);
}
