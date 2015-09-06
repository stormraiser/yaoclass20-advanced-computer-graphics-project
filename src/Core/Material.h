#pragma once

#include "Core/BSDF.h"

class Material{
private:
    static double emitFilterFunc(double t, double l);

public:
    BSDF *scatterBSDF, *surfaceBSDF;
    double ior, scatterRate;
    RGBColor filterColor, emitColor, scatterColor;
    bool doesScatter;

    Material(BSDF *_surfaceBSDF, double _ior = 1, RGBColor _filterColor = 1, BSDF *_scatterBSDF = 0,
             double _scatterRate = 1, RGBColor _scatterColor = 1, RGBColor _emitColor = 0):
        surfaceBSDF(_surfaceBSDF), scatterBSDF(_scatterBSDF), ior(_ior), scatterRate(_scatterRate),
            filterColor(_filterColor), emitColor(_emitColor), scatterColor(_scatterColor),
            doesScatter(_scatterBSDF != 0){}

    RGBColor emitFilter(double l);
};
