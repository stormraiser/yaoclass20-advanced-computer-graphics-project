#include "Mappings/BitmapMapping.h"

BitmapMapping::BitmapMapping(char *filename){
    int i, j, k;
    CImg<unsigned char> tmp;
    tmp.load(filename);
    w = tmp.width();
    h = tmp.height();
    bitmap.assign(w, h);
    for (i = 0; i < w; i++)
        for (j = 0; j < h; j++)
            bitmap(i, j) = (tmp(i, j, 0, 0) + tmp(i, j, 0, 1) + tmp(i, j, 0, 2)) / 3.0 / 255.0;
}

double BitmapMapping::value(const HitInfo &info) const{
    double tx = info.u * w;
    double ty = (1 - info.v) * h;
    return bitmap.cubic_atXY(tx, ty);
}
