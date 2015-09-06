#pragma once

#include "Core/Light.h"
#include "Primitives/LightSquare.h"

class SquareLight: public Light{
private:
    Point pos;
    Vector dir, up, right;
    double w, h;
    LightSquare *obj;

public:
    SquareLight(double px, double py, double pz, double dx, double dy, double dz, double ux, double uy, double uz, double _w, double _h, RGBColor _color, double _power);
    Ray shootRay();
    bool shootShadowRay(const Point &_pos, Ray &ray, RGBColor &_color);
    void emitPhoton(Ray &ray, RGBColor &_color);
    GeometricObject *associatedObject()
        {return obj;}
    bool isPointLight()
        {return false;}
};
