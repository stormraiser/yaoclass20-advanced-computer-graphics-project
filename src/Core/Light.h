#pragma once

#include "Utility/Arrays.h"
#include "Core/GeometricObject.h"

class Light{
public:
    RGBColor color;
    double power;

    Light(RGBColor _color, double _power):
        color(_color / _color.power()), power(_power){}
    virtual Ray shootRay() = 0;
    virtual bool shootShadowRay(const Point &_pos, Ray &ray, RGBColor &_color) = 0;
    virtual void emitPhoton(Ray &ray, RGBColor &_color) = 0;
    virtual GeometricObject *associatedObject()
        {return 0;}
    virtual bool isPointLight() = 0;
};
