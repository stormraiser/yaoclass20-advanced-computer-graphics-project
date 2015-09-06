#pragma once

#include "Core/Light.h"
#include "Core/Mapping.h"

class EnviromentLight: public Light{
private:
    Point center;
    double radius;
    Texture *texture;
    int resolution;
    RGBColor *cache;
    double *powerRec;
    double cr, cp;
    double tpower;
    HitInfo tmp;

    int randomIndex();

public:
    EnviromentLight(Point _center, double _radius, Texture *_texture, RGBColor _color, double _power, int _resolution);
    Ray shootRay();
    bool shootShadowRay(const Point &_pos, Ray &ray, RGBColor &_color);
    void emitPhoton(Ray &ray, RGBColor &_color);
    bool isPointLight()
        {return false;}

    RGBColor dirColor(Vector &dir);
};
