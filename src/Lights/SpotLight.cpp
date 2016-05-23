#include "Lights/SpotLight.h"
#include "Utility/func.h"

Ray SpotLight::shootRay(){
    Vector d;
    double ang;
    while (true){
        mapToSphere(randReal(), randReal(), d.x, d.y, d.z);
        ang = acos(d * dir) * RAD2DEG;
        if (ang < angle)
            return Ray(pos, d);
        else if (ang < angle + falloff)
            if (randReal() > (ang - angle) / (falloff))
                return Ray(pos, d);
    }
}

bool SpotLight::shootShadowRay(const Point &_pos, Ray &ray, RGBColor &_color){
    ray.o = _pos;
    ray.d = pos - _pos;
    double dis = ray.d.norm();
    ray.tMin = EPSILON;
    ray.tMax = dis - EPSILON;
    ray.d /= dis;
    double ang = acos(-ray.d * dir) * RAD2DEG;
    if (ang > angle + falloff)
        return false;
    else if (ang < angle)
        _color = color * power / (dis * dis * w);
    else
        _color = color * ((angle + falloff - ang) / falloff) * power / (dis * dis * w);
    return true;
}

void SpotLight::emitPhoton(Ray &ray, RGBColor &_color){
    ray = shootRay();
    _color = color;
}
