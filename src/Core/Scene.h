#pragma once

#include "Core/GeometricObject.h"
#include "Core/Mapping.h"
#include "Core/Light.h"
#include "Lights/EnviromentLight.h"
#include <vector>

using std::vector;

class Scene{
private:
    vector<GeometricObject*> objList;
    vector<double> powerSum;
    double totalPower;
    int lightCount;
    EnviromentLight *env;

public:
    enum RayType{HitAll, HitHigher, HitLower};
    vector<Light*> lights;

    Scene();

    void addObject(GeometricObject *obj);
    void addLight(Light *light);
    Ray shootLightRay();
    void emitPhoton(Ray &ray, RGBColor &color);
    //void buildScene();
    bool hit(Ray &ray);
    bool hit(Ray &ray, HitPoint &hitPoint, int type, int layer = 0);
    double power(){return totalPower;}
    RGBColor background(Vector &dir);
    void setEnviromentLight(EnviromentLight *_env);
};
