#include "Core/GeometricObject.h"

int GeometricObject::objectCount = 0;

int GeometricObject::count(){
    return objectCount;
}

void GeometricObject::resetCount(){
    objectCount = 0;
}
