#include "Core/Scene.h"
#include "Utility/func.h"

#include <cstdio>

Scene::Scene():
    totalPower(0), lightCount(0), env(0){
    powerSum.push_back(0);
}

void Scene::addObject(GeometricObject *obj){
    objList.push_back(obj);
}

bool Scene::hit(Ray &ray){
    int i;
    for (i = 0; i < objList.size(); i++)
        if (objList[i]->hit(ray))
            return true;
    return false;
}

bool Scene::hit(Ray &ray, HitPoint &hitPoint, int type, int layer){
    //printf("<");
    int i;
    HitPoint ht;
    bool f = false;
    switch(type){
        case HitAll:
            for (i = 0; i < objList.size(); i++)
                if (objList[i]->hit(ray, ht))
                    if ((!f) || (ht < hitPoint)){
                        f = true;
                        hitPoint = ht;
                    }
            break;
        case HitHigher:
            for (i = 0; i < objList.size(); i++)
                if ((objList[i]->layer > layer) && (objList[i]->hit(ray, ht)))
                    if ((ht.isInto()) && ((!f) || (ht < hitPoint))){
                        f = true;
                        hitPoint = ht;
                    }
            break;
        case HitLower:
            for (i = 0; i < objList.size(); i++)
                if ((objList[i]->layer < layer) && (objList[i]->hit(ray, ht)))
                    if ((!ht.isInto()) && ((!f) || (ht < hitPoint))){
                        f = true;
                        hitPoint = ht;
                    }
            break;
    }
    //printf(">\n");
    return f;
}

RGBColor Scene::background(Vector &dir){
    //printf("@@@@@\n");
    if (env == 0)
        return 0;
    else
        return env->dirColor(dir);
}

void Scene::addLight(Light* light){
    lights.push_back(light);
    totalPower += light->power;
    powerSum.push_back(totalPower);
    lightCount++;
    GeometricObject *obj = light->associatedObject();
    if (obj != 0)
        addObject(obj);
}

Ray Scene::shootLightRay(){
    double t = randReal() * totalPower;
    int zl = 0, zr = lightCount, m;
    while (zl + 1 < zr){
        m = (zl + zr) / 2;
        if (t > powerSum[m])
            zl = m;
        else
            zr = m;
    }
    return lights[zl]->shootRay();
}

void Scene::emitPhoton(Ray &ray, RGBColor &color){
    double t = randReal() * totalPower;
    int zl = 0, zr = lightCount, m;
    while (zl + 1 < zr){
        m = (zl + zr) / 2;
        if (t > powerSum[m])
            zl = m;
        else
            zr = m;
    }
    lights[zl]->emitPhoton(ray, color);
}

void Scene::setEnviromentLight(EnviromentLight *_env){
    env = _env;
    addLight(env);
}
