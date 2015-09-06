#include "BSDFs/FresnelBlendBSDF.h"
#include "Utility/func.h"

bool FresnelBlendBSDF::f(HitInfo &info) const{
    double p = fresnel(info.n1, info.n2, info.wo * info.shadeNormal);
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

bool FresnelBlendBSDF::diffuseF(HitInfo &info) const{
    double p = fresnel(info.n1, info.n2, info.wo * info.shadeNormal);
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

bool FresnelBlendBSDF::diffuseGlossyF(HitInfo &info) const{
    double p = fresnel(info.n1, info.n2, info.wo * info.shadeNormal);
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

bool FresnelBlendBSDF::s(HitInfo &info) const{
    if (randReal() < fresnel(info.n1, info.n2, info.wo * info.shadeNormal))
        return bsdf1->s(info);
    else
        return bsdf2->s(info);
}

bool FresnelBlendBSDF::specularS(HitInfo &info) const{
    if (randReal() < fresnel(info.n1, info.n2, info.wo * info.shadeNormal))
        return bsdf1->specularS(info);
    else
        return bsdf2->specularS(info);
}

bool FresnelBlendBSDF::specularGlossyS(HitInfo &info) const{
    if (randReal() < fresnel(info.n1, info.n2, info.wo * info.shadeNormal))
        return bsdf1->specularGlossyS(info);
    else
        return bsdf2->specularGlossyS(info);
}

bool FresnelBlendBSDF::ms(HitInfo &info) const{
    double t = info.shadeNormal * info.wo;
    double p = fresnel(info.n1, info.n2, t);
    if (bsdf2->s(info)){
        info.wi2 = info.wi;
        info.isReflected2 = info.isReflected;
        info.scattered2 = info.scattered * (1 - p);
        if (bsdf1->s(info)){
            info.hasSecondary = true;
            info.scattered *= p;
            return true;
        }
        else{
            info.hasSecondary = false;
            info.wi = info.wi2;
            info.isReflected = info.isReflected2;
            info.scattered = info.scattered2;
            return true;
        }
    }
    else{
        info.hasSecondary = false;
        if (bsdf1->s(info)){
            info.scattered *= p;
            return true;
        }
        else
            return false;
    }
}

bool FresnelBlendBSDF::specularMS(HitInfo &info) const{
    double t = info.shadeNormal * info.wo;
    double p = fresnel(info.n1, info.n2, t);
    if (bsdf2->specularS(info)){
        info.wi2 = info.wi;
        info.isReflected2 = info.isReflected;
        info.scattered2 = info.scattered * (1 - p);
        if (bsdf1->specularS(info)){
            info.hasSecondary = true;
            info.scattered *= p;
            return true;
        }
        else{
            info.hasSecondary = false;
            info.wi = info.wi2;
            info.isReflected = info.isReflected2;
            info.scattered = info.scattered2;
            return true;
        }
    }
    else{
        info.hasSecondary = false;
        if (bsdf1->specularS(info)){
            info.scattered *= p;
            return true;
        }
        else
            return false;
    }
}

bool FresnelBlendBSDF::specularGlossyMS(HitInfo &info) const{
    double t = info.shadeNormal * info.wo;
    double p = fresnel(info.n1, info.n2, t);
    if (bsdf2->specularGlossyS(info)){
        info.wi2 = info.wi;
        info.isReflected2 = info.isReflected;
        info.scattered2 = info.scattered * (1 - p);
        if (bsdf1->specularGlossyS(info)){
            info.hasSecondary = true;
            info.scattered *= p;
            return true;
        }
        else{
            info.hasSecondary = false;
            info.wi = info.wi2;
            info.isReflected = info.isReflected2;
            info.scattered = info.scattered2;
            return true;
        }
    }
    else{
        info.hasSecondary = false;
        if (bsdf1->specularGlossyS(info)){
            info.scattered *= p;
            return true;
        }
        else
            return false;
    }
}

