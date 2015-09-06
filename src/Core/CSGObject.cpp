#include "Core/CSGObject.h"
#include "Core/Primitive.h"
#include "Core/CSGNode.h"
#include <algorithm>
#include <cstdio>

#define CALL_PRIMITIVE(func)                                                    \
    for (list<Primitive*>::iterator i = plist.begin(); i != plist.end(); i++)   \
        (*i)->func;

#define OPERATOR_DEF(symbol, op)                                                               \
    CSGObject operator symbol(const CSGObject &a, const CSGObject &b){                         \
        CSGObject obj;                                                                         \
        CSGOperationNode *root = new CSGOperationNode(CSGOperationNode::op, a.root, b.root);   \
        obj.root = root;                                                                       \
        obj.plist.splice(obj.plist.end(), a.plist);                                            \
        obj.plist.splice(obj.plist.end(), b.plist);                                            \
        a.root->parent = root;                                                                 \
        b.root->parent = root;                                                                 \
        a.root = 0;                                                                            \
        b.root = 0;                                                                            \
        return obj;                                                                            \
    }                                                                                          \
                                                                                               \
    CSGObject operator symbol(const CSGObject &a, const PrimitivePtr &b){                      \
        return a symbol CSGObject(b);                                                          \
    }                                                                                          \
                                                                                               \
    CSGObject operator symbol(const PrimitivePtr &a, const CSGObject &b){                      \
        return CSGObject(a) symbol b;                                                          \
    }                                                                                          \
                                                                                               \
    CSGObject operator symbol(const PrimitivePtr &a, const PrimitivePtr &b){                   \
        return CSGObject(a) symbol CSGObject(b);                                               \
    }

CSGObject::CSGObject(PrimitivePtr primitivePtr){
    CSGPrimitiveNode *node = new CSGPrimitiveNode(primitivePtr);
    plist.clear();
    plist.push_back(primitivePtr);
    root = node;
    primitivePtr->parent = node;
    primitivePtr->csg = this;
}

OPERATOR_DEF(+, CSGUnion)
OPERATOR_DEF(-, CSGDifference)
OPERATOR_DEF(*, CSGIntersection)
OPERATOR_DEF(^, CSGSymmetricDifference)

void CSGObject::translate(double dx, double dy, double dz){
    CALL_PRIMITIVE(translate(dx, dy, dz));
}

void CSGObject::rotate(double ang, double ax, double ay, double az){
    CALL_PRIMITIVE(rotate(ang, ax, ay, az));
}

void CSGObject::scale(double sx, double sy, double sz){
    CALL_PRIMITIVE(scale(sx, sy, sz));
}

void CSGObject::shear(double dx, double dy, double dz, double sx, double sy, double sz){
    CALL_PRIMITIVE(shear(dx, dy, dz, sx, sy, sz));
}

bool CSGObject::hit(Ray ray){
    HitPoint p;
    return hit(ray, p);
}

bool CSGObject::hit(Ray ray, HitPoint &hitPoint){
    hitList.clear();
    CALL_PRIMITIVE(hit(ray, hitList));
    CALL_PRIMITIVE(parent->boolVal = false);
    std::sort(hitList.begin(), hitList.end());

    CSGPrimitiveNode *p;
    CSGOperationNode *q;
    bool boolVal = false;
    for (vector<HitPoint>::iterator i = hitList.begin(); i < hitList.end(); i++){
        if (i->t > ray.tMax)
            return false;
        p = i->obj->parent;
        if (i->type == HitPoint::HitInOut){
            p->boolVal = true;
            q = p->parent;
            while (q != 0){
                q->evaluateBool();
                q = q->parent;
            }
            if ((i->t > ray.tMin) && (root->boolVal != boolVal)){
                hitPoint = (*i);
                hitPoint.type = root->boolVal ? HitPoint::HitInOut : HitPoint::HitOutIn;
                return true;
            }
            p->boolVal = false;
            q = p->parent;
            while (q != 0){
                q->evaluateBool();
                q = q->parent;
            }
        }
        else{
            p->boolVal = (i->type == HitPoint::HitIn);
            q = p->parent;
            while (q != 0){
                q->evaluateBool();
                q = q->parent;
            }
            if ((i->t > ray.tMin) && (root->boolVal != boolVal)){
                hitPoint = (*i);
                hitPoint.type = root->boolVal ? HitPoint::HitIn : HitPoint::HitOut;
                return true;
            }
        }
        boolVal = root->boolVal;
    }
    return false;
}

void CSGObject::generateBoundingBox(){
    CALL_PRIMITIVE(generateBoundingBox())
    bBox = root->boundingBox();
}

int CSGObject::checkBoundingBox(const BoundingBox &box){
    return root->checkBoundingBox(box);
}

void CSGObject::setChildCSG(){
    CALL_PRIMITIVE(csg = this);
}
