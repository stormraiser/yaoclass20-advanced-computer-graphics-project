#include "Lights/SquareLight.h"
#include "Utility/func.h"
#include "BSDFs/EmittingBSDF.h"
#include <cstdio>

SquareLight::SquareLight(double px, double py, double pz, double dx, double dy, double dz, double ux, double uy, double uz, double _w, double _h, RGBColor _color, double _power):
    Light(_color, _power), pos(Point(px, py, pz)), dir(Vector(dx, dy, dz).normalized()), w(_w), h(_h){
    up = Vector(ux, uy, uz);
    up -= (up * dir) * dir;
    up.normalize();
    right = dir ^ up;
    obj = new LightSquare(pos, dir, up, right, w, h);
    EmittingBSDF *bsdf = new EmittingBSDF(color * power / (w * h));
    obj->material = new Material(bsdf);
}

Ray SquareLight::shootRay(){
    Ray ray;
    double u, v, w;
    ray.o = pos + up * (randReal() - 0.5) * h + right * (randReal() - 0.5) * w;
    mapToHemisphere(randReal(), randReal(), u, v, w, 1);
    ray.d = u * up + v * right + w * dir;
    ray.tMin = EPSILON;
    ray.tMax = INF;
    return ray;
}

bool SquareLight::shootShadowRay(const Point &_pos, Ray &ray, RGBColor &_color){
    if ((_pos - pos) * dir < 0)
        return false;
    ray.o = _pos;
    ray.d = pos + up * (randReal() - 0.5) * h + right * (randReal() - 0.5) * w - _pos;
    double dis = ray.d.norm();
    ray.d /= dis;
    ray.tMin = EPSILON;
    ray.tMax = dis - EPSILON;
    _color = color * power * (-dir * ray.d) / (dis * dis * PI);
    return true;
}

void SquareLight::emitPhoton(Ray &ray, RGBColor &_color){
    ray = shootRay();
    _color = color;
}
