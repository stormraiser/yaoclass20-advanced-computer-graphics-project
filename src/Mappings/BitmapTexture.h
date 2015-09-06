#pragma once

#include "Core/Mapping.h"
#include <CImg.h>

using namespace cimg_library;

class BitmapTexture: public Texture{
private:
    CImg<float> bitmap;
    int w, h;
    double uscale, vscale;

public:
    BitmapTexture(char *filename, double _uscale = 1, double _vscale = 1, bool isHDR = false);
    RGBColor value(const HitInfo &info) const;
};
