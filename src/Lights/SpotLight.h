#pragma once

#include "Core/Light.h"

class SpotLight: public Light{
private:
    Point pos;
    Vector dir;
    double angle, falloff, w;

public:
    SpotLight(double px, double py, double pz, double dx, double dy, double dz, double _angle, double _falloff, RGBColor _color = 1, double _power = 1):
        Light(_color, _power), pos(Point(px, py, pz)), dir(Vector(dx - px, dy - py, dz - pz).normalized()), angle(_angle), falloff(_falloff){}
    Ray shootRay();
    bool shootShadowRay(const Point &_pos, Ray &ray, RGBColor &_color);
    void emitPhoton(Ray &ray, RGBColor &_color);
    bool isPointLight()
        {return true;}
};
