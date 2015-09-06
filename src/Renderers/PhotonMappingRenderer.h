#pragma once

#include "Core/Renderer.h"
#include "Core/PhotonMap.h"

class PhotonMappingRenderer: public Renderer{
private:
    PhotonMap global, caustic, volume;
    int globalNum, causticNum, globalGatherNum, causticGatherNum;
    int globalCount, causticCount, totalEmit;
    int maxDepth, maxMultirayDepth;
    int sampleRate, finalGatherCount, shadowRayCount;
    int renderMode;

    RGBColor renderRay(Ray ray, int index);
    RGBColor visualizePhoton(Ray ray);
    RGBColor trace(Ray ray, int depth, int index, Primitive *currentObj, bool isPrimary);
    RGBColor direct(HitPoint &hitPoint, HitInfo &info);
    RGBColor indirect(HitPoint &hitPoint, HitInfo &info, Primitive *currentObject, Primitive *nextObject, int depth, int index);
    RGBColor volumeIndirect(HitInfo &info, Primitive *currentObject, int depth, int index);
    RGBColor specular(HitPoint &hitPoint, HitInfo &info, Primitive *currentObject, Primitive *nextObject, int depth, int index, bool isPrimary);
    RGBColor globalGather(BSDF *bsdf, HitInfo &info);
    RGBColor causticGather(BSDF *bsdf, HitInfo &info);
    RGBColor volumeGather(BSDF *bsdf, HitInfo &info, double scatterRate);

public:
    enum RenderModeFlag{
        DirectComponent = 0x01,
        SpecularComponent = 0x02,
        IndirectComponent = 0x04,
        CausticComponent = 0x08,
        NoGather = 0x10,
        PhotonVisualize = 0x20,
        AllowMultiray = 0x40
    };

    void buildPhotonMap();
    void savePhotonMap(char *filename);
    void loadPhotonMap(char *filename);
    PhotonMappingRenderer(Scene *_scene, Camera *_camera, Film *_film, int _sampleRate):
        Renderer(_scene, _camera, _film, _sampleRate){}
    void setPhotonNumber(int _globalNum, int _causticNum, int _globalGatherNum, int _causticGatherNum)
        {globalNum = _globalNum; causticNum = _causticNum; globalGatherNum = _globalGatherNum; causticGatherNum = _causticGatherNum;}
    void setQuality(int _finalGatherCount, int _shadowRayCount)
        {finalGatherCount = _finalGatherCount; shadowRayCount = _shadowRayCount;}
    void setMaximumDepth(int _maxDepth)
        {maxDepth = _maxDepth;}
    void setMaximumMultirayDepth(int _maxMultirayDepth)
        {maxMultirayDepth = _maxMultirayDepth;}
    void setRenderMode(int _renderMode)
        {renderMode = _renderMode;}
};
