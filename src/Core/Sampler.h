#pragma once

class Sampler{
private:
    int sampleRate;
    double *x, *y;
    double *ca, *cr;
    int *rx, *ry;

public:
    Sampler():
        x(0), y(0), ca(0), cr(0), rx(0), ry(0), sampleRate(-1){}
    ~Sampler();

    void generateSample(int _sampleRate, bool fCircle = false);
    void getSample(int index, double &_x, double &_y);
    void getPolygonSample(int index, double &_x, double &_y, int n, double offset = 0);
    void getCircleSample(int index, double &_x, double &_y);
};
