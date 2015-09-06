#pragma once

#include "Core/Mapping.h"
#include <CImg.h>

using namespace cimg_library;

class BitmapMapping: public Mapping{
private:
    CImg<float> bitmap;
    int w, h;

public:
    BitmapMapping(char *filename);
    double value(const HitInfo &info) const;
};

