#include "Lights/EnviromentLight.h"

#include <cstdio>

EnviromentLight::EnviromentLight(Point _center, double _radius, Texture *_texture, RGBColor _color, double _power, int _resolution):
    Light(_color, _power), center(_center), radius(_radius), texture(_texture), resolution(_resolution){
    int i, j;
    tpower = 0;
    cache = new RGBColor[resolution * resolution * 2];
    powerRec = new double[resolution * resolution * 2];
    for (i = 0; i < resolution * 2; i++)
        for (j = 0; j < resolution; j++){
            tmp.u = (i + 0.5) / (resolution * 2);
            tmp.v = (j + 0.5) / resolution;
            cache[i * resolution + j] = texture->value(tmp);
            powerRec[i * resolution + j] = cache[i * resolution + j].power() * (PI / resolution * sin(tmp.v * PI) * PI / resolution);
            tpower += powerRec[i * resolution + j];
        }
    for (i = 0; i < resolution * resolution * 2; i++)
        powerRec[i] /= tpower;
    for (i = 1; i < resolution * resolution * 2; i++)
        powerRec[i] += powerRec[i - 1];
    cr = power / (PI * radius * radius);
    printf("%f\n", tpower);
}

int EnviromentLight::randomIndex(){
    double t = randReal();
    int zl = 0, zr = resolution * resolution * 2, mid;
    if (t >= powerRec[0])
        while (zr - zl > 1){
            mid = (zl + zr) / 2;
            if (t < powerRec[mid])
                zr = mid;
            else
                zl = mid;
        }
    return zl;
}

Ray EnviromentLight::shootRay(){
    Ray ray;
    double theta, phi, sx, sy;
    int k = randomIndex();
    theta = (k / resolution + 0.5) / resolution * PI;
    phi = ((k % resolution + 0.5) / resolution - 0.5) * PI;
    ray.d = Vector(-cos(theta) * cos(phi), -sin(theta) * cos(phi), -sin(phi));
    Vector u = (ray.d ^ Vector(0, 0, 1)).normalized();
    Vector v = (ray.d ^ u).normalized();
    do{
        sx = randReal();
        sy = randReal();
    } while (sx * sx + sy * sy > 1);
    ray.o = center + sx * u + sy * v - radius * ray.d;
    return ray;
}

bool EnviromentLight::shootShadowRay(const Point &_pos, Ray &ray, RGBColor &_color){
    double theta, phi;
    int k = randomIndex();
    theta = (k / resolution + 0.5) / resolution * PI;
    phi = ((k % resolution + 0.5) / resolution - 0.5) * PI;
    ray.d = Vector(cos(theta) * cos(phi), sin(theta) * cos(phi), sin(phi));
    ray.o = _pos;
    _color = cache[k] / cache[k].power() * cr;
    ray.tMin = EPSILON;
    ray.tMax = 2 * radius;
    return true;
}

void EnviromentLight::emitPhoton(Ray &ray, RGBColor &_color){
    double theta, phi, sx, sy;
    int k = randomIndex();
    theta = (k / resolution + 0.5) / resolution * PI;
    phi = ((k % resolution + 0.5) / resolution - 0.5) * PI;
    ray.d = Vector(-cos(theta) * cos(phi), -sin(theta) * cos(phi), -sin(phi));
    Vector u = (ray.d ^ Vector(0, 0, 1)).normalized();
    Vector v = (ray.d ^ u).normalized();
    do{
        sx = randReal();
        sy = randReal();
    } while (sx * sx + sy * sy > 1);
    ray.o = center + sx * radius * u + sy * radius * v - radius * ray.d;
    _color = cache[k] / cache[k].power();
}

RGBColor EnviromentLight::dirColor(Vector &dir){
    dir.normalize();
    tmp.u = atan2(dir.x, dir.y) * 0.5 * INVPI;
    if (tmp.u < 0)
        tmp.u += 1;
    tmp.v = asin(dir.z) * INVPI + 0.5;
    RGBColor color = texture->value(tmp);
    return color / tpower * 4 * PI * cr;
}
