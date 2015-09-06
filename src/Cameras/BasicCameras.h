#pragma once

#include "Core/Camera.h"

class ParallelCamera: public Camera{
public:
    bool shootRay(double x, double y, Ray &ray);
};

class PerspectiveCamera: public Camera{
public:
    bool shootRay(double x, double y, Ray &ray);
};
