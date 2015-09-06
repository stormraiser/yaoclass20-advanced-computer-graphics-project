#include "Cameras/BasicCameras.h"
#include "Utility/func.h"

bool PerspectiveCamera::shootRay(double x, double y, Ray &ray){
    double ax = 0, ay = 0;
    // generate ax and ay from sampler
    do{
        ax = randReal();
        ay = randReal();
    } while (ax * ax + ay * ay > 1);
    Point focusPoint = pos + (lookDir + x * rightDir + y * upDir) * focalDis;
    ray.o = pos + ax * aperture * rightDir + ay * aperture * upDir;
    ray.d = (focusPoint - ray.o).normalized();
    return true;
}

