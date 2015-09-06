#include "Mappings/PerlinNoise3D.h"
#include "Utility/func.h"
#include <cstdlib>

PerlinNoise3D::PerlinNoise3D(int layerCount, double decayRate, int seed, char *filename, double _xScale, double _yScale, double _zScale, int _freq):
    xScale(_xScale), yScale(_yScale), zScale(_zScale), freq(_freq){
    CImg<double> tmp;
    int i, j, k, p, q, r, l, h;
    double vmin, vmax;
    srand(seed);
    colorMap.load(filename);
    size = 1 << (layerCount - 1);
    noiseImage.assign(size * 2, size * 2, size * 2, 1, 0);
    for (i = layerCount - 1; i >= 1; i--){
        l = 1 << i;
        tmp.assign(l * 2, l * 2, l * 2, 1);
        for (p = 0; p < l; p++)
            for (q = 0; q < l; q++)
                for (r = 0; r < l; r++)
                    tmp(p, q, r, 0) = randReal();
        for (p = 0; p < l; p++)
            for (q = 0; q < l; q++)
                for (r = 0; r < l; r++)
                    tmp(p, q, r + l, 0) = tmp(p, q, r, 0);
        for (p = 0; p < l; p++)
            for (q = 0; q < l; q++)
                for (r = 0; r < l * 2; r++)
                    tmp(p, q + l, r, 0) = tmp(p, q, r, 0);
        for (p = 0; p < l; p++)
            for (q = 0; q < l * 2; q++)
                for (r = 0; r < l * 2; r++)
                    tmp(p + l, q, r, 0) = tmp(p, q, r, 0);
        tmp.resize(l << (layerCount - i), l << (layerCount - i), l << (layerCount - i), 1, 3, 2);
        noiseImage = noiseImage * decayRate + tmp;
    }
    noiseImage.crop(size / 2 + 1, size / 2 + 1, size / 2 + 1, 0, size / 2 * 3, size / 2 * 3, size / 2 * 3, 0);
    vmin = noiseImage.min();
    vmax = noiseImage.max();
    printf("noise %f %f\n", vmin, vmax);
    noiseImage = (noiseImage - vmin) / (vmax - vmin);
    len = colorMap.width();
    h = colorMap.height();
    for (i = 0; i < len; i++)
        for (j = 1; j < h; j++)
            for (k = 0; k < 3; k++)
                colorMap(i, 0, 0, k) += colorMap(i, j, 0, k);
    colorMap /= 255;
    colorMap /= h;
}

RGBColor PerlinNoise3D::value(const HitInfo &info) const{
    double x = info.hitPoint.x / xScale;
    double y = info.hitPoint.y / yScale;
    double z = info.hitPoint.z / zScale;
    while (x < 0)
        x += 1;
    while (x > 1)
        x -= 1;
    while (y < 0)
        y += 1;
    while (y > 1)
        y -= 1;
    while (z < 0)
        z += 1;
    while (z > 1)
        z -= 1;
    double t = noiseImage.cubic_atXYZ(x * size, y * size, z * size) * freq;
    while (t > 1)
        t -= 1;
    RGBColor ret;
    ret.r = colorMap.cubic_atX(t * len, 0, 0, 0);
    ret.g = colorMap.cubic_atX(t * len, 0, 0, 1);
    ret.b = colorMap.cubic_atX(t * len, 0, 0, 2);
    return ret;
}
