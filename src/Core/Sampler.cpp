#include "Core/Sampler.h"
#include "Utility/def.h"
#include "Utility/func.h"
#include <cmath>
#include <cstdlib>

Sampler::~Sampler(){
    if (x != 0){
        delete [] x;
        delete [] y;
        delete [] rx;
        delete [] ry;
    }
    if (ca != 0){
        delete [] ca;
        delete [] cr;
    }
}

void Sampler::generateSample(int _sampleRate, bool fCircle){
    int &s = sampleRate;
    int i, j, k, t;
    double r, d, x0, y0, p;
    if (_sampleRate > s){
        s = _sampleRate;
        if (x != 0){
            delete [] x;
            delete [] y;
            delete [] rx;
            delete [] ry;
        }
        x = new double[s * s];
        y = new double[s * s];
        rx = new int[s * s];
        ry = new int[s * s];
    }
    /*
    for (i = 0; i < s; i++)
        for (j = 0; j < s; j++){
            rx[i * s + j] = s - j - 1;
            ry[i * s + j] = i;
        }
    for (i = s - 1; i >= 1; i--){
        k = rand() % (i + 1);
        for (j = 0; j < s; j++){
            t = rx[i * s + j];
            rx[i * s + j] = rx[k * s + j];
            rx[k * s + j] = t;
            t = ry[i * s + j];
            ry[i * s + j] = ry[k * s + j];
            ry[k * s + j] = t;
        }
    }
    for (i = 0; i < s; i++){
        for (j = s - 1; j >= 1; j--){
            k = rand() % (i + 1);
            t = rx[i * s + j];
            rx[i * s + j] = rx[i* s + k];
            rx[i * s + k] = t;
            t = ry[i * s + j];
            ry[i * s + j] = ry[i * s + k];
            ry[i * s + k] = t;
        }
    }
    for (i = 0; i < s; i++)
        for (j = 0; j < s; j++){
            x[i * s + j] = (i * s + rx[i * s + j] + randReal()) / (s * s);
            y[i * s + j] = (j * s + ry[i * s + j] + randReal()) / (s * s);
        }
    */
    /*
    for (i = 0; i < s; i++)
        for (j = 0; j < s; j++){
            x[i * s + j] = (i + randReal()) / s;
            y[i * s + j] = (j + randReal()) / s;
        }
    */

    for (i = 0; i < s; i++)
        for (j = 0; j < s; j++){
            x[i * s + j] = randReal();
            y[i * s + j] = randReal();
        }

    for (i = s * s - 1; i >= 1; i--){
        j = rand() % (i + 1);
        p = x[i];
        x[i] = x[j];
        x[j] = p;
        p = y[i];
        y[i] = y[j];
        y[j] = p;
    }
    if (fCircle){
        if (_sampleRate > s){
            s = _sampleRate;
            if (ca != 0){
                delete [] ca;
                delete [] cr;
            }
            ca = new double[s * s];
            cr = new double[s * s];
        }
        for (i = 0; i < s * s; i++){
            x0 = x[i] * 2 - 1;
            y0 = y[i] * 2 - 1;
            if (x0 > y0)
                if (x0 + y0 > 0){
                    r = x0;
                    d = y0 / r / 8;
                }
                else{
                    r = -y0;
                    d = (x0 / r - 2) / 8;
                }
            else
                if (x0 + y0 > 0){
                    r = y0;
                    d = (2 - x0 / r) / 8;
                }
                else{
                    r = -x0;
                    d = (4 - y0 / r) / 8;
                }
            ca[i] = d;
            cr[i] = r;
        }
    }
}

void Sampler::getSample(int index, double &_x, double &_y){
    _x = x[index];
    _y = y[index];
}

void Sampler::getCircleSample(int index, double &_x, double &_y){
    _x = cr[index] * cos(ca[index] * 2 * PI);
    _x = cr[index] * sin(ca[index] * 2 * PI);
}

void Sampler::getPolygonSample(int index, double &_x, double &_y, int n, double offset){
    double t = round(ca[index] * n + offset);
    double d1 = (ca[index] * n - t) * 2 - 1;
    double d2 = atan2(sin(PI / n) * d1, cos(PI / n));
    double r = cos(PI / n) / cos(d2);
    double d = t * 2 * PI / n + d2;
    _x = r * cos(d);
    _y = r * sin(d);
}
