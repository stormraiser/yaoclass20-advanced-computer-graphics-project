#pragma once

#define cimg_use_openexr
#include <CImg.h>
#include "Utility/Arrays.h"
#include "Core/Sampler.h"
#include <vector>
#include <tuple>

using namespace std;
using namespace cimg_library;

class Film{
private:
    double scale;
    double dcolor[3];
    int currentIndex;
    int xmin, xmax, ymin, ymax, sampleRate;
    int w, h;
    int cx, cy;
    //Sampler *sampler;
    CImg<float> image, dispImage;
    CImgDisplay disp;
    bool directDisplay;
    vector<tuple<int, int, int> > sampleList;

public:
    Film(double _scale = 100, int _xmin = -100, int _xmax = 100, int _ymin = -100, int _ymax = 100):
        scale(_scale), xmin(_xmin), xmax(_xmax), ymin(_ymin), ymax(_ymax){}

    void setScale(double _scale)
        {scale = _scale;}
    void setViewArea(int _xmin, int _xmax, int _ymin, int _ymax)
        {xmin = _xmin; xmax = _xmax; ymin = _ymin; ymax = _ymax;}
    void setSampleRate(int _sampleRate)
        {sampleRate = _sampleRate;}
    void setDirectDisplay(bool _directDisplay)
        {directDisplay = _directDisplay;}

    void start();
    void finish();
    int totalPixel()
        {return (xmax - xmin) * (ymax - ymin);}
    void getSample(int k, double &x, double &y);
    void setResult(const RGBColor &color);
    void saveImage(char *filename, bool isHDR = false);
};
