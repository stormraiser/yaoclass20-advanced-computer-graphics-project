#pragma once

#include "Core/Scene.h"
#include "Core/Camera.h"
#include "Core/Film.h"

using std::vector;

class Renderer{
protected:
    int sampleRate;
    Scene *scene;
    Camera *camera;
    Film *film;

    virtual RGBColor renderRay(Ray ray, int index) = 0;

public:
    Renderer(Scene *_scene, Camera *_camera, Film *_film, int _sampleRate);
    void render();
};
