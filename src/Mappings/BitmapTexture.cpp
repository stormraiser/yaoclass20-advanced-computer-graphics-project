#include "Mappings/BitmapTexture.h"
#include <cmath>

BitmapTexture::BitmapTexture(char *filename, double _uscale, double _vscale, bool isHDR){
    int i, j, k;
    if (isHDR)
        bitmap.load_exr(filename);
    else
        bitmap.load(filename);
    w = bitmap.width();
    h = bitmap.height();
    if (!isHDR){
        bitmap /= 255;
        for (i = 0; i < w; i++)
            for (j = 0; j < h; j++)
                for (k = 0; k < 3; k++)
                    bitmap(i, j, 0, k) = pow(bitmap(i, j, 0, k), 3);
    }
    uscale = _uscale;
    vscale = _vscale;
}

RGBColor BitmapTexture::value(const HitInfo &info) const{
    double u = info.u * uscale;
    while (u > 1)
        u -= 1;
    double v = info.v * vscale;
    while (v > 1)
        v -= 1;
    double tx = u * w;
    double ty = (1 - v) * h;
    double r = bitmap.cubic_atXY(tx, ty, 0, 0);
    double g = bitmap.cubic_atXY(tx, ty, 0, 1);
    double b = bitmap.cubic_atXY(tx, ty, 0, 2);
    return RGBColor(r, g, b);
}
