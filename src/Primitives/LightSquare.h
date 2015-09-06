#pragma once

#include "Core/Primitive.h"

class LightSquare: public Primitive{
private:
    Point pos;
    Vector dir, up, right;
    double w, h;

public:
    LightSquare(Point _pos, Vector _dir, Vector _up, Vector _right, double _w, double _h):
        Primitive(0), pos(_pos), dir(_dir), up(_up), right(_right), w(_w), h(_h){}

    PRIMITIVE_FUNC

    BoundingBox baseBoundingBox()
        {return BoundingBox();}
};
