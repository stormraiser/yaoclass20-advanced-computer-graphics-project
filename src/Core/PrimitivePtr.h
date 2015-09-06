#pragma once

class PrimitivePtr{
public:
    Primitive *primitive;

    PrimitivePtr(Primitive *_primitive):
        primitive(_primitive){}

    operator Primitive*()
        {return primitive;}
    Primitive *operator->()
        {return primitive;}
};
