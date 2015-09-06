#include "Cameras/BasicCameras.h"

bool ParallelCamera::shootRay(double x, double y, Ray &ray){
    ray = Ray(pos + x * rightDir + y * upDir, lookDir);
    return true;
}
