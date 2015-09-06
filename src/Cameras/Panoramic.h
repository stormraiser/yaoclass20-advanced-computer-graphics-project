#pragma once

#include "Core/Camera.h"

class Panoramic: public Camera{
protected:
    virtual bool getAngle(double r, double &ang) = 0;

public:
    bool shootRay(double x, double y, Ray &ray);
};
