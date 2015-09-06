#pragma once

#include "Core/Light.h"

class PointLight: public Light{
private:
    Point pos;

public:
    PointLight(double x, double y, double z, RGBColor _color = 1, double _power = 1):
        Light(_color, _power), pos(Point(x, y, z)){}
    Ray shootRay();
    bool shootShadowRay(const Point &_pos, Ray &ray, RGBColor &_color);
    void emitPhoton(Ray &ray, RGBColor &_color);
    bool isPointLight()
        {return true;}
};
