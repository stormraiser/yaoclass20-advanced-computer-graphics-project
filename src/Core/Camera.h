#pragma once

#include "Utility/Arrays.h"
#include "Core/Ray.h"

class Camera{
protected:
    Point pos;
    Vector lookDir, upDir, rightDir;
    double aperture, focalDis;
    bool dofEnabled;

public:
    void setPosition(double x, double y, double z, double lx, double ly, double lz, double ux = 0, double uy = 0, double uz = 1);
    void focus(double _focalDis);
    void focus(double x, double y, double z);
    void setDofEnabled(bool f);
    void setAperture(double _aperture);

    virtual bool shootRay(double x, double y, Ray &ray) = 0;
};
