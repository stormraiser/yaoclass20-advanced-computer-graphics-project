#pragma once

#include "Utility/Arrays.h"
#include "Core/Ray.h"
#include "Core/HitPoint.h"

struct HitInfo{
    enum ScatterType{Specular, Glossy, Diffuse};

    Ray ray;                        // original ray

    // filled during intersection test
    double t;                       // hitPoint == ray.o + t * ray.d
    int tag;                        // generated and used by geometric objects
    HitPoint::HitType hitType;                    // is the ray shooting into or out of an object

    // filled while requesting information about hitpoint from geometric objects
    int face;                       // face id, used for selecting from a set of textures
    Point hitPoint, localPoint;     // global and local hit point
    Normal normal;                  // face normal
    Normal shadeNormal;             // interpolated & bump mapped normal for shading
    double u, v;                    // texture coordinates
    Vector du, dv;                  // direction of +u and +v, for bump mapping
    //Material *material;

    // filled by tracer
    Vector wo;                      // (reversed) direction of current ray
    double n1, n2;                  // indices of refraction
    double sx, sy;                  // random sample

    // filled by either tracer or BSDF
    Vector wi, wi2;                      // directrion of next ray to trace

    // filled by BSDF
    bool hasSecondary;
    bool isReflected, isReflected2;               // was the ray reflected or transmitted
    ScatterType type, type2;
    RGBColor emitted;
    RGBColor scattered, scattered2;
    double pdf;

    void set(const HitPoint &hitPoint)
        {t = hitPoint.t; tag = hitPoint.tag; hitType = hitPoint.type;}
};
