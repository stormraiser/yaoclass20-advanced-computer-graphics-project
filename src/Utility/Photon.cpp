#include "Utility/Photon.h"
#include "Utility/def.h"
#include <cmath>

Photon::Photon(Point pos, Vector dir, RGBColor color){
    int er, eg, eb, em, cr, cg, cb, i, d1, d2;
    double sr, sg, sb;
    x = pos.x;
    y = pos.y;
    z = pos.z;
    sr = frexp(color.r, &er);
    sg = frexp(color.g, &eg);
    sb = frexp(color.b, &eb);
    em = (er > eg ? (er > eb ? er : eb) : (eg > eb ? eg : eb));
    em = em > 127 ? 127 : em < -128 ? -128 : em;
    for (i = er; i < em; i++)
        sr /= 2;
    for (i = eg; i < em; i++)
        sg /= 2;
    for (i = eb; i < em; i++)
        sb /= 2;
    cr = sr * 256 - 0.5;
    cr = cr > 255 ? 255 : cr < 0 ? 0 : cr;
    cg = sg * 256 - 0.5;
    cg = cg > 255 ? 255 : cg < 0 ? 0 : cg;
    cb = sb * 256 - 0.5;
    cb = cb > 255 ? 255 : cb < 0 ? 0 : cb;
    r = cr;
    g = cg;
    b = cb;
    e = em;
    d1 = (atan2(dir.y, dir.x) * INVPI * 0.5 + 0.5) * 256 - 0.5;
    d1 = d1 > 255 ? 255 : d1 < 0 ? 0 : d1;
    d2 = (asin(dir.z / dir.norm()) * INVPI + 0.5) * 256 - 0.5;
    d2 = d2 > 255 ? 255 : d2 < 0 ? 0 : d2;
    theta = d1;
    phi = d2;
}

RGBColor Photon::color(){
    return RGBColor(r + 0.5, g + 0.5, b + 0.5) / 256 * pow(2, e);
}

Point Photon::pos(){
    return Point(x, y, z);
}

Vector Photon::dir(){
    //return photonDir[theta][phi];
    ///*
    double d1 = ((theta + 0.5) / 256 - 0.5) * PI * 2;
    double d2 = ((phi + 0.5) / 256 - 0.5) * PI;
    return Vector(cos(d2) * cos(d1), cos(d2) * sin(d1), sin(d2));
    //*/
}
