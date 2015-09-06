#include "Core/Renderer.h"
#include "Utility/Arrays.h"
#include "Utility/func.h"
#include "Core/CSGObject.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

Renderer::Renderer(Scene *_scene, Camera *_camera, Film *_film, int _sampleRate):
    scene(_scene), camera(_camera), film(_film), sampleRate(_sampleRate){
    film->setSampleRate(sampleRate);
}

void Renderer::render(){
    srand(time(0));
    int n, i, j;
    Ray ray;
    double x, y;
    film->start();
    n = film->totalPixel();
    for (i = 0; i < n; i++){
        if (i % 100 == 0)
            printf("# %d\n", i);
        /*
        for (j = 0; j < maxDepth; j++)
            samplers[j]->generateSample(sampleRate);
        */
        for (j = 0; j < sampleRate * sampleRate; j++){
            film->getSample(i * sampleRate * sampleRate + j, x, y);
            if (camera->shootRay(x, y, ray)){
                ray.tMin = EPSILON;
                ray.tMax = INF;
                film->setResult(renderRay(ray, j));
            }
            else
                film->setResult(0);
        }
    }
    film->finish();
}
