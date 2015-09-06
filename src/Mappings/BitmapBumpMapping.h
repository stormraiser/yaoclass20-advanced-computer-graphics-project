#pragma once

#include "Core/Mapping.h"
#include <CImg.h>

using namespace cimg_library;

class BitmapBumpMapping: public BumpMapping{
private:
    CImg<double> hbitmap, vbitmap, hkernel, vkernel;
    int w, h;
    double uscale, vscale;

public:
    BitmapBumpMapping(char *filename, double scale, double _uscale = 1, double _vscale = 1);
    pair<double, double> value(const HitInfo &info) const;
};
