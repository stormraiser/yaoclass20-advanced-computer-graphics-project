#pragma once

#include "Core/Renderer.h"

class MonteCarloPathTracer: public Renderer{
private:
    int maxDepth;

    RGBColor renderRay(Ray ray, int index);

public:
    MonteCarloPathTracer(Scene *_scene, Camera *_camera, Film *_film, int _sampleRate):
        Renderer(_scene, _camera, _film, _sampleRate){}
    void setMaximumDepth(int _maxDepth)
        {maxDepth = _maxDepth;}
    RGBColor directLighting(Primitive *obj, HitInfo &info);
    RGBColor trace(Ray ray, int depth, int index, Primitive *currentObj);
};
