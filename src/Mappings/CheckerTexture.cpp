#include "Mappings/CheckerTexture.h"

RGBColor CheckerTexture::value(const HitInfo &info) const{
    int x = floor(info.u * uScale + uOffset);
    int y = floor(info.v * vScale + vOffset);
    if ((x + y) % 2 == 0)
        return texture1->value(info);
    else
        return texture2->value(info);
}
