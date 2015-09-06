#include "Mappings/CheckerColor.h"

RGBColor CheckerColor::value(const HitInfo &info) const{
    int x = floor(info.u * uScale + uOffset);
    int y = floor(info.v * vScale + vOffset);
    if ((x + y) % 2 == 0)
        return color1;
    else
        return color2;
}
