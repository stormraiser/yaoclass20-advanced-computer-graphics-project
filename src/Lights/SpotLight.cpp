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

    double t0 = angle * DEG2RAD;
    double t1 = (angle + falloff) * DEG2RAD;
    w = (1 - cos(t0) + t1 / (t1 - t0) * (cos(t0) - cos(t1)) + 1 / (t1 - t0) * (t1 * cos(t1) - t0 * cos(t0) - sin(t1))) * 0.5;
}

bool SpotLight::shootShadowRay(const Point &_pos, Ray &ray, RGBColor &_color){
    ray.o = _pos;
    ray.d = pos - _pos;
    double dis = ray.d.norm();
    ray.tMin = EPSILON;
    ray.tMax = dis - EPSILON;
    ray.d /= dis;
    double ang = acos(-ray.d * dir / dis) * RAD2DEG;
    if (ang > angle + falloff)
        return false;
    else if (ang < angle)
        _color = color / w * power / (dis * dis);
    else
        _color = color * (angle + falloff - ang) / falloff / w * power / (dis * dis * 4 * PI);
}

void SpotLight::emitPhoton(Ray &ray, RGBColor &_color){
    ray = shootRay();
    _color = color;
}
