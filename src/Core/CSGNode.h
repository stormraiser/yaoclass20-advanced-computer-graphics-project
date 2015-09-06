#pragma once
#include "Core/GeometricObject.h"

class Primitive;

struct CSGOperationNode;

struct CSGNode{
    CSGOperationNode *parent;
    bool boolVal;

    CSGNode():
        parent(0), boolVal(false){}

    virtual BoundingBox boundingBox() = 0;
    virtual int checkBoundingBox(const BoundingBox &box) = 0;
};

struct CSGOperationNode: public CSGNode{
    CSGNode *left, *right;
    enum Operation{CSGUnion, CSGIntersection, CSGDifference, CSGSymmetricDifference};
    Operation op;

    CSGOperationNode(Operation _op, CSGNode *_left, CSGNode *_right):
        CSGNode(), op(_op), left(_left), right(_right){}

    void evaluateBool();
    BoundingBox boundingBox();
    int checkBoundingBox(const BoundingBox &box);
};

struct CSGPrimitiveNode: public CSGNode{
    Primitive *primitive;

    CSGPrimitiveNode(Primitive *_primitive = 0):
        CSGNode(), primitive(_primitive){}

    BoundingBox boundingBox();
    int checkBoundingBox(const BoundingBox &box);
};
