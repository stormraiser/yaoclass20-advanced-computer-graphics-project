#include "BSDFs/EmittingBSDF.h"

bool EmittingBSDF::emit(HitInfo &info) const{
    if (info.face == 0){
        info.emitted = color;
        return true;
    }
    else
        return false;
}
