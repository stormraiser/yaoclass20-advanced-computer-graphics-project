#pragma once

#include "Core/Mapping.h"
#include <CImg.h>

using namespace cimg_library;

class PerlinNoise3D: public Texture{
private:
    CImg<double> noiseImage;
    CImg<double> colorMap;
    int size, len;
    double xScale, yScale, zScale;
    int freq;

public:
    PerlinNoise3D(int layerCount, double decayRate, int seed, char *filename, double _xScale, double _yScale, double _zScale, int _freq);
    RGBColor value(const HitInfo &info) const;
};
