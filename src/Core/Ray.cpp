#include "Core/Ray.h"

long long Ray::rayCount = 0;

Ray &Ray::operator++(){
    timeStamp = ++rayCount;
    return *this;
}
