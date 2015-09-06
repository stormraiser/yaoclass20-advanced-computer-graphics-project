#pragma once

#include "Utility/Arrays.h"

struct Photon{
    float x, y, z;
    unsigned char r, g, b;
    signed char e;
    unsigned char theta, phi;
    unsigned char flag;

    Photon(){}
    Photon(Point pos, Vector dir, RGBColor color);
    RGBColor color();
    Point pos();
    Vector dir();
};

extern const Vector photonDir[256][256];
