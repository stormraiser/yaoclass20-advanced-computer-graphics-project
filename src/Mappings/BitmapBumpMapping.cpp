#include "Mappings/BitmapBumpMapping.h"

#include <cstdio>

const int kx[5] = {-24, 80, 0, -80, 24};
const int ky[5] = {7, 63, 116, 63, 7};

BitmapBumpMapping::BitmapBumpMapping(char *filename, double scale, double _uscale, double _vscale){
    int i, j, k;
    CImg<double> tmp;
    tmp.load(filename);
    hkernel.assign(5, 5, 1, 1);
    vkernel.assign(5, 5, 1, 1);
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++){
            hkernel(i, j, 0, 0) = -kx[i] * ky[j] / 65536.0;
            vkernel(j, i, 0, 0) = kx[i] * ky[j] / 65536.0;
        }
    w = tmp.width();
    h = tmp.height();
    hbitmap.assign(w, h, 1, 1, 0);
    for (i = 0; i < w; i++)
        for (j = 0; j < h; j++)
            for (k = 0; k < tmp.spectrum(); k++)
                hbitmap(i, j, 0, 0) += tmp(i, j, 0, k);
    vbitmap = hbitmap;
    hbitmap.convolve(hkernel, 1);
    vbitmap.convolve(vkernel, 1);
    /*
    tmp = hbitmap;
    tmp.max(0.0);
    tmp.min(255);
    tmp.save("dh.png");
    tmp = vbitmap;
    tmp.max(0.0);
    tmp.min(255);
    tmp.save("dv.png");
    */
    hbitmap *= w * _uscale;
    hbitmap /= (255 * tmp.spectrum());
    hbitmap *= scale;
    vbitmap *= h * _vscale;
    vbitmap /= (255 * tmp.spectrum());
    vbitmap *= scale;
    uscale = _uscale;
    vscale = _vscale;
}

pair<double, double> BitmapBumpMapping::value(const HitInfo &info) const{
    double u = info.u * uscale;
    while (u > 1)
        u -= 1;
    double v = info.v * vscale;
    while (v > 1)
        v -= 1;
    double tx = u * w;
    double ty = (1 - v) * h;
    return pair<double, double>(hbitmap.cubic_atXY(tx, ty), vbitmap.cubic_atXY(tx, ty));
}
