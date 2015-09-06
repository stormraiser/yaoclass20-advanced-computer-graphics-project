#include "BSDFs/MappingBlendedBSDF.h"
#include "Utility/func.h"
#include <cstdio>

bool MappingBlendedBSDF::f(HitInfo &info) const{
    double p = mapping->value(info);
    bool ft = false;
    RGBColor color = 0;
    if (bsdf1->f(info)){
        ft = true;
        color += info.scattered * p;
    }
    if (bsdf2->f(info)){
        ft = true;
        color += info.scattered * (1 - p);
    }
    info.scattered = color;
    return ft;
}

bool MappingBlendedBSDF::diffuseF(HitInfo &info) const{
    double p = mapping->value(info);
    bool ft = false;
    RGBColor color = 0;
    if (bsdf1->diffuseF(info)){
        ft = true;
        color += info.scattered * p;
    }
    if (bsdf2->diffuseF(info)){
        ft = true;
        color += info.scattered * (1 - p);
    }
    info.scattered = color;
    return ft;
}

bool MappingBlendedBSDF::diffuseGlossyF(HitInfo &info) const{
    double p = mapping->value(info);
    bool ft = false;
    RGBColor color = 0;
    if (bsdf1->diffuseGlossyF(info)){
        ft = true;
        color += info.scattered * p;
    }
    if (bsdf2->diffuseGlossyF(info)){
        ft = true;
        color += info.scattered * (1 - p);
    }
    info.scattered = color;
    return ft;
}

bool MappingBlendedBSDF::s(HitInfo &info) const{
    if (randReal() < mapping->value(info))
        return bsdf1->s(info);
    else
        return bsdf2->s(info);
}

bool MappingBlendedBSDF::specularS(HitInfo &info) const{
    if (randReal() < mapping->value(info))
        return bsdf1->specularS(info);
    else
        return bsdf2->specularS(info);
}

bool MappingBlendedBSDF::specularGlossyS(HitInfo &info) const{
    if (randReal() < mapping->value(info))
        return bsdf1->specularGlossyS(info);
    else
        return bsdf2->specularGlossyS(info);
}
