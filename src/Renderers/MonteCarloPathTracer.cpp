#include "Renderers/MonteCarloPathTracer.h"
#include "Core/Primitive.h"
#include "Core/CSGObject.h"
#include "Utility/func.h"

RGBColor MonteCarloPathTracer::renderRay(Ray ray, int index){
    return trace(ray, 0, index, 0);
}

RGBColor MonteCarloPathTracer::directLighting(Primitive *obj, HitInfo &info){
    /*
    Point lightPos;
    if (!scene->getLightSample(lightPos))
        return 0;
    Ray ray;
    ++ray;
    ray.o = info.hitPoint;
    ray.d = lightPos - ray.o;
    double l = ray.d.norm();
    ray.d /= l;
    ray.tMin = EPSILON;
    ray.tMax = l;
    if (scene->hit(ray))
        return 0;
    else
        return
    */
    return 0;
}

RGBColor MonteCarloPathTracer::trace(Ray ray, int depth, int index, Primitive *currentObj){
    /*
    if (!(ray.d.norm() < 10000)){
        printf("%d %d\n", depth, currentObj == 0 ? -1 : currentObj->id);
        printf("%lf %lf %lf\n", ray.o.x, ray.o.y, ray.o.z);
        printf("%lf %lf %lf\n", ray.d.x, ray.d.y, ray.d.z);
    }
    */
    if (!(ray.d.norm() < 10000))
        return 0;
    HitPoint hitPoint, ht;
    HitInfo info;
    RGBColor scattered, emitted, light;
    Point lightPos;
    info.ray = ++ray;
    bool f;
    if (currentObj == 0){
        if (scene->hit(ray, hitPoint, Scene::HitAll)){
            info.t = hitPoint.t;
            info.tag = hitPoint.tag;
            hitPoint.obj->getHitInfo(info);
            info.wo = -ray.d.normalized();
            info.n1 = 1;
            info.n2 = hitPoint.obj->material->ior;
            //samplers[depth]->getSample(index, info.sx, info.sy);
            info.sx = randReal();
            info.sy = randReal();
            if (depth == maxDepth - 1)
                return directLighting(hitPoint.obj, info);
            else{
                if (!hitPoint.obj->material->surfaceBSDF->s(info))
                    return info.emitted;
                if (!info.isReflected)
                    currentObj = hitPoint.obj;
                ray.o = info.hitPoint;
                ray.d = info.wi;
                ray.tMin = EPSILON;
                ray.tMax = INF;
                //
                //printf("#1 %lf\n", info.t);
                //printf("%lf %lf %lf\n", ray.o.x, ray.o.y, ray.o.z);
                scattered = info.scattered * trace(ray, depth + 1, index, currentObj) * fabs(info.normal * info.wi) / info.pdf;
                return info.emitted + scattered;
            }
        }
        return scene->background(ray.d);
    }
    else{
        //printf("%d\n", currentObj->id);
        Material *material = currentObj->material;
        double l;
        if (material->doesScatter)
            l = log(randReal()) / log(material->scatterRate);
        double l2;
        ray.tMin = EPSILON;
        ray.tMax = INF;
        bool ft;
        if (currentObj->csg == 0)
            ft = currentObj->hit(ray, hitPoint);
        else
            ft = currentObj->csg->hit(ray, hitPoint);
        /*
        if (!ft)
            printf("! %d %d %d\n", currentObj->id, ft, hitPoint.tag);
        */
        double tMax = hitPoint.t;
        ray.tMax = tMax;
        if (scene->hit(ray, ht, Scene::HitHigher, currentObj->layer)){
            l2 = ht.t * ray.d.norm();
            if ((!material->doesScatter) || (l2 < l)){
                info.t = ht.t;
                info.tag = ht.tag;
                ht.obj->getHitInfo(info);
                info.wo = -ray.d.normalized();
                info.n1 = material->ior;
                info.n2 = ht.obj->material->ior;
                //samplers[depth]->getSample(index, info.sx, info.sy);
                info.sx = randReal();
                info.sy = randReal();
                f = ht.obj->material->surfaceBSDF->s(info);
                if (depth == maxDepth - 1)
                    return directLighting(hitPoint.obj, info);
                else{
                    if (!hitPoint.obj->material->surfaceBSDF->s(info))
                        return info.emitted;
                    if (!info.isReflected)
                        currentObj = ht.obj;
                    ray.o = info.hitPoint;
                    ray.d = info.wi;
                    ray.tMin = EPSILON;
                    ray.tMax = INF;
                    //
                    //printf("#2 %lf\n", info.t);
                    //printf("%lf %lf %lf\n", ray.o.x, ray.o.y, ray.o.z);
                    l2 *= material->ior;
                    //emitted = material->emitFilter(l2);
                    emitted = 0;
                    scattered = info.scattered * trace(ray, depth + 1, index, currentObj) * fabs(info.normal * info.wi) / info.pdf;
                    return (info.emitted + scattered) * pow(material->filterColor, l2) + emitted;
                }
            }
            else{
                info.wo = -ray.d.normalized();
                //samplers[depth]->getSample(index, info.sx, info.sy);
                info.sx = randReal();
                info.sy = randReal();
                f = material->scatterBSDF->s(info);
                if ((depth == maxDepth - 1) || (!f))
                    return info.emitted;
                else{
                    ray.o = info.ray.o + l * info.ray.d / info.ray.d.norm();
                    ray.d = info.wi;
                    ray.tMin = -EPSILON;
                    ray.tMax = INF;
                    l *= material->ior;
                    //emitted = material->emitFilter(l);
                    emitted = 0;
                    scattered = material->scatterColor * info.scattered * trace(ray, depth + 1, index, currentObj);
                    return (info.emitted + scattered) * pow(material->filterColor, l2) + emitted;
                }
            }
        }
        else{
            l2 = tMax * ray.d.norm();
            if ((material->doesScatter) && (l < l2)){
                info.wo = -ray.d.normalized();
                //samplers[depth]->getSample(index, info.sx, info.sy);
                info.sx = randReal();
                info.sy = randReal();
                f = material->scatterBSDF->s(info);
                if ((depth == maxDepth - 1) || (!f))
                    return info.emitted;
                else{
                    ray.o = info.ray.o + l * info.ray.d / info.ray.d.norm();
                    ray.d = info.wi;
                    ray.tMin = -EPSILON;
                    ray.tMax = INF;
                    l *= material->ior;
                    //emitted = material->emitFilter(l);
                    emitted = 0;
                    scattered = material->scatterColor * info.scattered * trace(ray, depth + 1, index, currentObj);
                    return (info.emitted + scattered) * pow(material->filterColor, l) + emitted;
                }
            }
            else{
                info.t = tMax;
                info.tag = hitPoint.tag;
                //printf("! %d\n", info.tag);
                //if (!ft)
                //    printf("<");
                currentObj->getHitInfo(info);
                info.wo = -ray.d.normalized();
                info.n1 = material->ior;
                ray.tMin = tMax;
                ray.tMax = INF;
                bool f2 = scene->hit(ray, ht, Scene::HitLower, currentObj->layer);
                if (f2)
                    info.n2 = ht.obj->material->ior;
                else
                    info.n2 = 1;
                //samplers[depth]->getSample(index, info.sx, info.sy);
                info.sx = randReal();
                info.sy = randReal();
                if (depth == maxDepth - 1)
                    return directLighting(hitPoint.obj, info);
                else{
                    if (!hitPoint.obj->material->surfaceBSDF->s(info))
                        return info.emitted;
                    if (!info.isReflected)
                        if (f2)
                            currentObj = ht.obj;
                        else
                            currentObj = 0;
                    //printf("%d\n", f2);
                    ray.o = info.hitPoint;
                    ray.d = info.wi;
                    ray.tMin = EPSILON;
                    ray.tMax = INF;
                    //
                    //printf("#3 %lf\n", info.t);
                    //printf("%lf %lf %lf\n", ray.o.x, ray.o.y, ray.o.z);
                    l2 *= material->ior;
                    //emitted = material->emitFilter(l2);
                    emitted = 0;
                    scattered = info.scattered * trace(ray, depth + 1, index, currentObj) * fabs(info.normal * info.wi) / info.pdf;
                    return (info.emitted + scattered) * pow(material->filterColor, l2) + emitted;
                }
            }
        }
    }
}
