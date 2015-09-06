#include "Renderers/PhotonMappingRenderer.h"
#include "Utility/func.h"
#include "Core/Primitive.h"
#include "Core/CSGObject.h"

#include <cstdio>

void PhotonMappingRenderer::buildPhotonMap(){
    globalCount = 0;
    causticCount = 0;
    totalEmit = 0;
    Ray ray;
    RGBColor color, cs;
    HitPoint ht, ht2;
    HitInfo info;
    bool f, f2, isCaustic;
    Primitive *currentObj;
    int depth;
    double scatterDis, p, insideLength, insideHit;

    while ((globalCount < globalNum) || (causticCount < causticNum)){
        totalEmit++;
        printf("%d %d\n", globalCount, causticCount);
        scene->emitPhoton(ray, color);
        isCaustic = true;
        depth = 0;
        currentObj = 0;
        while (true){
            //
            info.sx = randReal();
            info.sy = randReal();
            ray.tMin = EPSILON;
            ray.tMax = INF;
            info.wo = -ray.d.normalized();
            info.ray = ++ray;
            //printf("%f %f %f\n", color.r, color.g, color.b);
            depth++;
            if (currentObj == 0){
                if (!scene->hit(ray, ht, Scene::HitAll))
                    break;
                info.set(ht);
                ht.obj->getHitInfo(info);
                //
                Point pp = ray.o + ray.d * ht.t;
                //printf("%d %d %f %f %f\n", ht.obj->id, depth, pp.x, pp.y, pp.z);
                //printf("%d %d %f %f %f\n", ht.obj->id, depth, info.hitPoint.x, info.hitPoint.y, info.hitPoint.z);
                info.n1 = 1;
                info.n2 = ht.obj->material->ior;
                f = ht.obj->material->surfaceBSDF->s(info);
                if ((ht.obj->material->surfaceBSDF->hasDiffuseComponent())){
                    if (globalCount >= globalNum)
                        global.replace(info.hitPoint, ray.d, color);
                    else
                        global.insert(info.hitPoint, ray.d, color);
                    globalCount++;
                    if ((isCaustic) && (depth > 1)){
                        //printf("%f %f %f\n", info.hitPoint.x, info.hitPoint.y, info.hitPoint.z);
                        //printf("c1\n");
                        if (causticCount >= causticNum)
                            caustic.replace(info.hitPoint, ray.d, color);
                        else
                            caustic.insert(info.hitPoint, ray.d, color);
                        causticCount++;
                    }
                }
                if ((!f) || (depth == maxDepth))
                    break;
                if (info.type == HitInfo::Diffuse)
                    isCaustic = false;
                cs = color * info.scattered * fabs(info.shadeNormal * info.wi);
                p = cs.power() / color.power();
                if (randReal() > p)
                    break;
                color = cs / p;
                ray.o = info.hitPoint;
                ray.d = info.wi;
                if ((!info.isReflected) && ht.objChanged())
                    currentObj = ht.obj;
            }
            else{
                if (currentObj->material->doesScatter)
                    scatterDis = log(randReal()) / log(currentObj->material->scatterRate);
                else
                    scatterDis = INF;
                if (currentObj->csg == 0)
                    currentObj->hit(ray, ht);
                else
                    currentObj->csg->hit(ray, ht);
                insideLength = ray.d.norm() * ht.t;
                ray.tMax = ht.t;
                if (scene->hit(ray, ht2, Scene::HitHigher, currentObj->layer))
                    insideHit = ray.d.norm() * ht2.t;
                else
                    insideHit = INF;
                if ((insideHit < insideLength) && (insideHit < scatterDis)){
                    cs = color * pow(currentObj->material->filterColor, insideHit * currentObj->material->ior);
                    p = cs.power() / color.power();
                    if (randReal() > p)
                        break;
                    color = cs / p;
                    info.set(ht2);
                    ht2.obj->getHitInfo(info);
                    info.n1 = currentObj->material->ior;
                    info.n2 = ht2.obj->material->ior;
                    f = ht.obj->material->surfaceBSDF->s(info);
                    if (ht.obj->material->surfaceBSDF->hasDiffuseComponent()){
                        if (globalCount >= globalNum)
                            global.replace(info.hitPoint, ray.d, color);
                        else
                            global.insert(info.hitPoint, ray.d, color);
                        globalCount++;
                        if (isCaustic && (depth > 1)){
                            //printf("c2\n");
                            if (causticCount >= causticNum)
                                caustic.replace(info.hitPoint, ray.d, color);
                            else
                                caustic.insert(info.hitPoint, ray.d, color);
                            causticCount++;
                        }
                    }
                    if ((!f) || (depth == maxDepth))
                        break;
                    if (info.type == HitInfo::Diffuse)
                        isCaustic = false;
                    cs = color * info.scattered * fabs(info.shadeNormal * info.wi);
                    p = cs.power() / color.power();
                    if (randReal() > p)
                        break;
                    color = cs / p;
                    ray.o = info.hitPoint;
                    ray.d = info.wi;
                    if ((!info.isReflected) && ht2.objChanged())
                        currentObj = ht2.obj;
                }
                else if ((scatterDis < insideLength) && (scatterDis < insideHit)){
                    cs = color * pow(currentObj->material->filterColor, scatterDis * currentObj->material->ior);
                    p = cs.power() / color.power();
                    if (randReal() > p)
                        break;
                    color = cs / p;
                    info.hitPoint = ray.o + ray.d / ray.d.norm() * scatterDis;
                    f = currentObj->material->scatterBSDF->s(info);
                    if (globalCount >= globalNum)
                        volume.replace(info.hitPoint, ray.d, color);
                    else
                        volume.insert(info.hitPoint, ray.d, color);
                    if ((!f) || (depth == maxDepth))
                        break;
                    isCaustic = false;
                    cs = color * info.scattered;
                    p = cs.power() / color.power();
                    if (randReal() > p)
                        break;
                    color = cs / p;
                    ray.o = info.hitPoint;
                    ray.d = info.wi;
                }
                else{
                    cs = color * pow(currentObj->material->filterColor, insideLength * currentObj->material->ior);
                    p = cs.power() / color.power();
                    if (randReal() > p)
                        break;
                    color = cs / p;
                    info.set(ht);
                    currentObj->getHitInfo(info);
                    info.n1 = currentObj->material->ior;
                    ray.tMin = ht.t;
                    f2 = scene->hit(ray, ht2, Scene::HitLower, currentObj->layer);
                    if (f2)
                        info.n2 = ht2.obj->material->ior;
                    else
                        info.n2 = 1;
                    f = currentObj->material->surfaceBSDF->s(info);
                    if (ht.obj->material->surfaceBSDF->hasDiffuseComponent()){
                        if (globalCount >= globalNum)
                            global.replace(info.hitPoint, ray.d, color);
                        else
                            global.insert(info.hitPoint, ray.d, color);
                        globalCount++;
                        if (isCaustic && (depth > 1)){
                            //printf("c3\n");
                            if (causticCount >= causticNum)
                                caustic.replace(info.hitPoint, ray.d, color);
                            else
                                caustic.insert(info.hitPoint, ray.d, color);
                            causticCount++;
                        }
                    }
                    if ((!f) || (depth == maxDepth))
                        break;
                    if (info.type == HitInfo::Diffuse)
                        isCaustic = false;
                    cs = color * info.scattered * fabs(info.shadeNormal * info.wi);
                    p = cs.power() / color.power();
                    if (randReal() > p)
                        break;
                    color = cs / p;
                    ray.o = info.hitPoint;
                    ray.d = info.wi;
                    if ((!info.isReflected) && ht.objChanged())
                        if (f2)
                            currentObj = ht2.obj;
                        else
                            currentObj = 0;
                }
            }
        }
    }
    printf("# %d %d\n", globalCount, causticCount);
    printf("# %d %d %d\n", global.photonList.size(), volume.photonList.size(), caustic.photonList.size());
    global.buildPhotonMap();
    volume.buildPhotonMap();
    caustic.buildPhotonMap();
}

void PhotonMappingRenderer::savePhotonMap(char *filename){
    FILE *fout = fopen(filename, "w");
    fprintf(fout, "%d %d %d\n", globalCount, causticCount, totalEmit);
    global.save(fout);
    volume.save(fout);
    caustic.save(fout);
    fclose(fout);
}

void PhotonMappingRenderer::loadPhotonMap(char *filename){
    FILE *fin = fopen(filename, "r");
    fscanf(fin, "%d %d %d\n", &globalCount, &causticCount, &totalEmit);
    global.load(fin);
    volume.load(fin);
    caustic.load(fin);
    fclose(fin);
}

RGBColor PhotonMappingRenderer::visualizePhoton(Ray ray){
    RGBColor photonColor;
    bool f = false;
    double t;
    HitPoint ht;
    HitInfo info;

    info.ray = ++ray;
    //printf("# 1");
    if (scene->hit(ray, ht, Scene::HitAll)){
        info.set(ht);
        ht.obj->getHitInfo(info);
        global.volumeGather(info.hitPoint, 0.05, 1);
        caustic.volumeGather(info.hitPoint, 0.05, 1);
        //global.surfaceGather(info.hitPoint, info.normal, 0.1, 0.1, 1);
        //caustic.surfaceGather(info.hitPoint, info.normal, 0.1, 0.1, 1);
    }
    else
        return 0;
    //printf("# 2");
    if (global.gatheredPhoton.size() > 0)
        if ((!f) || (global.gatheredPhoton.begin()->first < t)){
            t = global.gatheredPhoton.begin()->first;
            photonColor = global.photonList[global.gatheredPhoton.begin()->second].color();
            f = true;
        }
    //printf("# 3");
    if (caustic.gatheredPhoton.size() > 0)
        if ((!f) || (caustic.gatheredPhoton.begin()->first < t)){
            t = caustic.gatheredPhoton.begin()->first;
            photonColor = caustic.photonList[caustic.gatheredPhoton.begin()->second].color();
            f = true;
        }
    //printf("# 4");
    //if (f)
    //    printf("! %f %f %f\n", photonColor.r, photonColor.g, photonColor.b);
    if (f)
        return photonColor;
    else
        return 0;
}

RGBColor PhotonMappingRenderer::indirect(HitPoint &hitPoint, HitInfo &info, Primitive *currentObject, Primitive *nextObject, int depth, int index){
    if (((renderMode & IndirectComponent) == 0) || (!hitPoint.obj->material->surfaceBSDF->hasDiffuseComponent()) || (depth >= maxDepth))
        return 0;
    Ray ray;
    int i;
    Primitive *newObject;
    RGBColor ret = 0;

    ray.o = info.hitPoint;
    ray.tMin = EPSILON;
    ray.tMax = INF;
    for (i = 0; i < finalGatherCount; i++){
        info.sx = randReal();
        info.sy = randReal();
        hitPoint.obj->material->surfaceBSDF->s(info);
        ray.d = info.wi;
        if ((!info.isReflected) && hitPoint.objChanged())
            newObject = nextObject;
        else
            newObject = currentObject;
        ret += info.scattered * fabs(info.shadeNormal * info.wi) * trace(ray, depth + 1, index, newObject, false) / finalGatherCount;
    }
    return ret;
}

RGBColor PhotonMappingRenderer::volumeIndirect(HitInfo &info, Primitive *currentObject, int depth, int index){
    if (((renderMode & IndirectComponent) == 0) || (depth >= maxDepth))
        return 0;
    Ray ray;
    int i;
    RGBColor ret = 0;

    ray.o = info.hitPoint;
    ray.tMin = EPSILON;
    ray.tMax = INF;
    for (i = 0; i < finalGatherCount; i++){
        info.sx = randReal();
        info.sy = randReal();
        currentObject->material->scatterBSDF->s(info);
        ray.d = info.wi;
        ret += info.scattered * trace(ray, depth + 1, index, currentObject, false) / finalGatherCount;
    }
    return ret;
}

RGBColor PhotonMappingRenderer::specular(HitPoint &hitPoint, HitInfo &info, Primitive *currentObject, Primitive *nextObject, int depth, int index, bool isPrimary){
    if (((renderMode & SpecularComponent) == 0) || (depth >= maxDepth))
        return 0;
    if (((renderMode & AllowMultiray) == 0) || (depth >= maxMultirayDepth)){
        if (!hitPoint.obj->material->surfaceBSDF->specularGlossyS(info))
            return 0;
    }
    else
        if (!hitPoint.obj->material->surfaceBSDF->specularGlossyMS(info))
            return 0;

    Ray ray;
    Primitive *newObject;
    RGBColor ret = 0;

    ray.o = info.hitPoint;
    ray.d = info.wi;
    ray.tMin = EPSILON;
    ray.tMax = INF;
    if ((!info.isReflected) && hitPoint.objChanged())
        newObject = nextObject;
    else
        newObject = currentObject;
    ret += info.scattered * trace(ray, depth + 1, index, newObject, isPrimary) * fabs(info.shadeNormal * info.wi);
    if ((info.hasSecondary) && ((renderMode & AllowMultiray) != 0) && (depth < maxMultirayDepth)){
        ray.d = info.wi2;
        if (info.isReflected2)
            newObject = currentObject;
        else
            newObject = nextObject;
        ret += info.scattered2 * trace(ray, depth + 1, index, newObject, isPrimary) * fabs(info.shadeNormal * info.wi2);
        //printf("1 %f %f %f\n", info.scattered.r, info.scattered.g, info.scattered.b);
        //printf("2 %f %f %f\n", info.scattered2.r, info.scattered2.g, info.scattered2.b);
    }
    return ret;
}

RGBColor PhotonMappingRenderer::direct(HitPoint &hitPoint, HitInfo &info){
    if ((renderMode & DirectComponent) == 0)
        return 0;
    int i, j, n = scene->lights.size();
    Ray ray;
    RGBColor lightColor, ret = 0;
    ret += hitPoint.obj->material->surfaceBSDF->emit(info);
    if (!hitPoint.obj->material->surfaceBSDF->hasDiffuseComponent())
        return ret;
    for (i = 0; i < n; i++)
        if (scene->lights[i]->isPointLight()){
            scene->lights[i]->shootShadowRay(info.hitPoint, ray, lightColor);
            ++ray;
            if (!scene->hit(ray)){
                info.wi = ray.d;
                hitPoint.obj->material->surfaceBSDF->f(info);
                ret += info.scattered * lightColor * fabs(info.shadeNormal * info.wi);
            }
        }
        else
            for (j = 0; j < shadowRayCount; j++){
                scene->lights[i]->shootShadowRay(info.hitPoint, ray, lightColor);
                ++ray;
                if (!scene->hit(ray)){
                    info.wi = ray.d;
                    hitPoint.obj->material->surfaceBSDF->f(info);
                    ret += info.scattered * lightColor * fabs(info.shadeNormal * info.wi) / shadowRayCount;
                }
            }
    return ret;
}

RGBColor PhotonMappingRenderer::globalGather(BSDF *bsdf, HitInfo &info){
    double searchRadius = 20 * sqrt(scene->power() * globalGatherNum / totalEmit);
    //double searchRadius = INF;

    int n, i;
    double r, w = 0, rt, wt;
    RGBColor ret = 0;
    vector<pair<double, int> >::iterator q;

    //global.surfaceGather(info.hitPoint, info.normal, searchRadius, 0.1, globalGatherNum);
    global.volumeGather(info.hitPoint, searchRadius, globalGatherNum);
    if (global.gatheredPhoton.size() == 0)
        return 0;
    r = global.currentRadius;
    i = 0;
    for (q = global.gatheredPhoton.begin(); q != global.gatheredPhoton.end(); q++){
        Photon &p = global.photonList[q->second];
        rt = (p.pos() - info.hitPoint).norm();
        info.wi = -p.dir();
        bsdf->f(info);
        i++;
        ///*
        if (i == globalGatherNum)
            wt = (r - rt) / 2;
        else
            wt = r - rt;
        //*/
        //wt = 1;
        w += wt;
        ret += wt * p.color() * info.scattered * fabs(info.shadeNormal * info.wi);
    }
    ret = ret / (w * PI * r * r) * globalGatherNum / totalEmit * scene->power();
    return ret;
}

RGBColor PhotonMappingRenderer::causticGather(BSDF *bsdf, HitInfo &info){
    if (((renderMode & CausticComponent) == 0) || (!bsdf->hasDiffuseComponent()))
        return 0;
    double searchRadius = 20 * sqrt(scene->power() * causticGatherNum / globalCount);
    //double searchRadius = INF;

    int n, i;
    double r, w = 0, rt, wt;
    RGBColor ret = 0;
    vector<pair<double, int> >::iterator q;

    //caustic.surfaceGather(info.hitPoint, info.normal, searchRadius, 0.1, causticGatherNum);
    caustic.volumeGather(info.hitPoint, searchRadius, causticGatherNum);
    if (caustic.gatheredPhoton.size() == 0)
        return 0;
    r = caustic.currentRadius;
    i = 0;
    for (q = caustic.gatheredPhoton.begin(); q != caustic.gatheredPhoton.end(); q++){
        Photon &p = caustic.photonList[q->second];
        rt = (p.pos() - info.hitPoint).norm();
        info.wi = -p.dir();
        bsdf->f(info);
        i++;
        if (i == causticGatherNum)
            wt = (r - rt) / 2;
        else
            wt = r - rt;
        w += wt;
        ret += wt * p.color() * info.scattered * fabs(info.shadeNormal * info.wi);
    }
    ret = ret / (w * PI * r * r) * causticGatherNum / totalEmit * scene->power();
    return ret;
}

RGBColor PhotonMappingRenderer::volumeGather(BSDF *bsdf, HitInfo &info, double scatterRate){
    double searchRadius = 20 * pow(scene->power() * globalGatherNum / totalEmit / (1 - scatterRate), 1.0 / 3);
    //double searchRadius = INF;

    int n, i;
    double r, w = 0, rt, wt;
    RGBColor ret = 0;
    vector<pair<double, int> >::iterator q;

    volume.volumeGather(info.hitPoint, searchRadius, globalGatherNum);
    if (volume.gatheredPhoton.size() == 0)
        return 0;
    r = volume.currentRadius;
    i = 0;
    for (q = volume.gatheredPhoton.begin(); q != volume.gatheredPhoton.end(); q++){
        Photon &p = volume.photonList[q->second];
        rt = (p.pos() - info.hitPoint).norm();
        info.wi = -p.dir();
        bsdf->f(info);
        i++;
        ///*
        if (i == globalGatherNum)
            wt = (r - rt) / 2;
        else
            wt = r - rt;
        //*/
        //wt = 1;
        w += wt;
        ret += wt * p.color() * info.scattered;
    }
    ret = ret / (w * PI * r * r * r * 4 / 3) * globalGatherNum / totalEmit * scene->power();
    return ret;
}

RGBColor PhotonMappingRenderer::trace(Ray ray, int depth, int index, Primitive *currentObj, bool isPrimary){
    HitPoint hitPoint, ht, ht2;
    HitInfo info;
    bool f;
    RGBColor ret = 0;
    int i;
    double scatterDis, insideLength, insideHit;

    //printf("> %d %d\n", depth, currentObj == 0 ? -1 : currentObj->id);
    //printf("%f %f %f %f %f %f\n", ray.o.x, ray.o.y, ray.o.z, ray.d.x, ray.d.y, ray.d.z);

    ray.tMin = EPSILON;
    ray.tMax = INF;
    info.ray = ++ray;
    info.sx = randReal();
    info.sy = randReal();
    info.wo = -ray.d.normalized();
    info.n1 = currentObj == 0 ? 1 : currentObj->material->ior;
    if (currentObj == 0){
        //printf(">> 1\n");
        if (scene->hit(ray, hitPoint, Scene::HitAll)){
            info.set(hitPoint);
            hitPoint.obj->getHitInfo(info);
            //printf("@ %f %f %f\n", info.hitPoint.x, info.hitPoint.y, info.hitPoint.z);
            //printf("^ %f %f %f\n", info.normal.x, info.normal.y, info.normal.z);
            //printf("^ %f %f %f\n", info.shadeNormal.x, info.shadeNormal.y, info.shadeNormal.z);
            info.n2 = hitPoint.obj->material->ior;
        }
        else
            return scene->background(ray.d);
        if (isPrimary){
            ret += direct(hitPoint, info);
            ret += indirect(hitPoint, info, currentObj, hitPoint.obj, depth, index);
            ret += specular(hitPoint, info, currentObj, hitPoint.obj, depth, index, true);
            ret += causticGather(hitPoint.obj->material->surfaceBSDF, info);
            return ret;
        }
        else{
            ret += globalGather(hitPoint.obj->material->surfaceBSDF, info);
            ret += specular(hitPoint, info, currentObj, hitPoint.obj, depth, index, false);
            return ret;
        }
    }
    else{
        if (currentObj->material->doesScatter)
            scatterDis = log(randReal()) / log(currentObj->material->scatterRate);
        else
            scatterDis = INF;
        if (currentObj->csg == 0){
            if (!currentObj->hit(ray, ht)){
                printf("!\n");
                //printf("> %d %d\n", depth, currentObj == 0 ? -1 : currentObj->id);
                //printf("%f %f %f %f %f %f\n", ray.o.x, ray.o.y, ray.o.z, ray.d.x, ray.d.y, ray.d.z);
                return 0;
            }
        }
        else{
            if (!currentObj->csg->hit(ray, ht)){
                //printf("!\n");
                //printf("> %d %d\n", depth, currentObj == 0 ? -1 : currentObj->id);
                //printf("%f %f %f %f %f %f\n", ray.o.x, ray.o.y, ray.o.z, ray.d.x, ray.d.y, ray.d.z);
                return 0;
            }
        }
        //printf("* %f\n", ht.t);
        insideLength = ray.d.norm() * ht.t;
        ray.tMax = ht.t;
        if (scene->hit(ray, ht2, Scene::HitHigher, currentObj->layer))
            insideHit = ray.d.norm() * ht2.t;
        else
            insideHit = INF;
        //printf("%f %f %f\n", scatterDis, insideHit, insideLength);
        if ((insideHit < scatterDis) && (insideHit < insideLength)){
            //printf(">> 2\n");
            info.set(ht2);
            ht2.obj->getHitInfo(info);
            info.n2 = ht2.obj->material->ior;
            if (isPrimary){
                ret += direct(ht2, info);
                ret += indirect(ht2, info, currentObj, ht2.obj, depth, index);
                ret += specular(ht2, info, currentObj, ht2.obj, depth, index, true);
                ret += causticGather(ht2.obj->material->surfaceBSDF, info);
                return ret * pow(currentObj->material->filterColor, insideHit * currentObj->material->ior);
            }
            else{
                ret += globalGather(ht2.obj->material->surfaceBSDF, info);
                ret += specular(ht2, info, currentObj, ht2.obj, depth, index, false);
                return ret * pow(currentObj->material->filterColor, insideHit * currentObj->material->ior);
            }
        }
        else if ((insideLength < scatterDis) && (insideLength < insideHit)){
            //printf(">> 3\n");
            ray.tMin = ht.t;
            ray.tMax = INF;
            Primitive *nextObject;
            if (scene->hit(ray, ht2, Scene::HitLower, currentObj->layer)){
                nextObject = ht2.obj;
                info.n2 = ht2.obj->material->ior;
            }
            else{
                nextObject = 0;
                info.n2 = 1;
            }
            info.set(ht);
            ht.obj->getHitInfo(info);
            if (isPrimary){
                ret += direct(ht, info);
                ret += indirect(ht, info, currentObj, nextObject, depth, index);
                ret += specular(ht, info, currentObj, nextObject, depth, index, true);
                ret += causticGather(ht.obj->material->surfaceBSDF, info);
                return ret * pow(currentObj->material->filterColor, insideLength * currentObj->material->ior);
            }
            else{
                ret += globalGather(ht.obj->material->surfaceBSDF, info);
                ret += specular(ht, info, currentObj, nextObject, depth, index, false);
                return ret * pow(currentObj->material->filterColor, insideLength * currentObj->material->ior);
            }
        }
        else{
            info.hitPoint = ray.o + ray.d / ray.d.norm() * scatterDis;
            if (isPrimary){
                ret += volumeIndirect(info, currentObj, depth, index);
                return ret;
            }
            else{
                ret += volumeGather(currentObj->material->scatterBSDF, info, currentObj->material->scatterRate);
                return ret;
            }
        }
    }
}

RGBColor PhotonMappingRenderer::renderRay(Ray ray, int index){
    if ((renderMode & PhotonVisualize) != 0)
        return visualizePhoton(ray);
    return trace(ray, 0, index, 0, (renderMode & NoGather) == 0);
}
