#include "Lights/PointLight.h"
#include "Utility/func.h"

Ray PointLight::shootRay(){
    double x, y, z;
    mapToSphere(randReal(), randReal(), x, y, z);
    return Ray(pos, Vector(x, y, z));
}

bool PointLight::shootShadowRay(const Point &_pos, Ray &ray, RGBColor &_color){
    ray.o = _pos;
    ray.d = pos - _pos;
    double dis = ray.d.norm();
    ray.tMin = EPSILON;
    ray.tMax = dis - EPSILON;
    ray.d /= dis;
    _color = color * power / (dis * dis * 4 * PI);
    return true;
}

void PointLight::emitPhoton(Ray &ray, RGBColor &_color){
    ray = shootRay();
    _color = color;
}
