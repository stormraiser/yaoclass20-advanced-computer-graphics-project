#include "Core/CSGNode.h"
#include "Core/Primitive.h"
#include <algorithm>

using std::max;
using std::min;

void CSGOperationNode::evaluateBool(){
    switch (op){
        case CSGUnion:
            boolVal = left->boolVal || right->boolVal;
            break;
        case CSGIntersection:
            boolVal = left->boolVal && right->boolVal;
            break;
        case CSGDifference:
            boolVal = left->boolVal && !(right->boolVal);
            break;
        case CSGSymmetricDifference:
            boolVal = left->boolVal ^ right->boolVal;
    }
}

BoundingBox CSGPrimitiveNode::boundingBox(){
    return primitive->boundingBox();
}

BoundingBox CSGOperationNode::boundingBox(){
    switch (op){
        case CSGUnion:
        case CSGSymmetricDifference:
            return left->boundingBox().extend(right->boundingBox());
        case CSGDifference:
            return left->boundingBox();
        case CSGIntersection:
            return left->boundingBox().intersect(right->boundingBox());
    }
}

int CSGPrimitiveNode::checkBoundingBox(const BoundingBox &box){
    return primitive->checkBoundingBox(box);
}

int CSGOperationNode::checkBoundingBox(const BoundingBox &box){
    int l = left->checkBoundingBox(box), r = right->checkBoundingBox(box);
    switch (op){
        case CSGUnion:
            return max(l, r);
        case CSGIntersection:
            return min(l, r);
        case CSGDifference:
            return min(l, 2 - r);
        case CSGSymmetricDifference:
            if ((l == 1) || (l == 1))
                return 1;
            else
                return (l + r) % 4;
    }
}
