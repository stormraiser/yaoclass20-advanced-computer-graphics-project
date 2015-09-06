#include "Core/Primitive.h"
#include "Utility/def.h"
#include <cmath>

void Primitive::transformRay(Ray &ray){
    inverse.operatePoint(ray.o);
    inverse.operateVector(ray.d);
}

void Primitive::translate(double dx, double dy, double dz){
    Matrix tmp;
    tmp.d[0][3] = dx;
    tmp.d[1][3] = dy;
    tmp.d[2][3] = dz;
    matrix = tmp * matrix;
    tmp.d[0][3] = -dx;
    tmp.d[1][3] = -dy;
    tmp.d[2][3] = -dz;
    inverse *= tmp;
}

void Primitive::rotate(double ang, double ax, double ay, double az){
    double c = cos(ang * DEG2RAD);
    double s = sin(ang * DEG2RAD);
    Matrix tmp;
    tmp.d[0][0] = (1 - c) * ax * ax + c;
    tmp.d[0][1] = (1 - c) * ax * ay - az * s;
    tmp.d[0][2] = (1 - c) * ax * az + ay * s;
    tmp.d[1][0] = (1 - c) * ay * ax + az * s;
    tmp.d[1][1] = (1 - c) * ay * ay + c;
    tmp.d[1][2] = (1 - c) * ay * az - ax * s;
    tmp.d[2][0] = (1 - c) * az * ax - ay * s;
    tmp.d[2][1] = (1 - c) * az * ay + ax * s;
    tmp.d[2][2] = (1 - c) * az * az + c;
    matrix = tmp * matrix;
    tmp.d[0][0] = (1 - c) * ax * ax + c;
    tmp.d[0][1] = (1 - c) * ax * ay + az * s;
    tmp.d[0][2] = (1 - c) * ax * az - ay * s;
    tmp.d[1][0] = (1 - c) * ay * ax - az * s;
    tmp.d[1][1] = (1 - c) * ay * ay + c;
    tmp.d[1][2] = (1 - c) * ay * az + ax * s;
    tmp.d[2][0] = (1 - c) * az * ax + ay * s;
    tmp.d[2][1] = (1 - c) * az * ay - ax * s;
    tmp.d[2][2] = (1 - c) * az * az + c;
    inverse *= tmp;
}

void Primitive::scale(double s){
    Matrix tmp;
    tmp.d[0][0] = s;
    tmp.d[1][1] = s;
    tmp.d[2][2] = s;
    matrix = tmp * matrix;
    tmp.d[0][0] = 1 / s;
    tmp.d[1][1] = 1 / s;
    tmp.d[2][2] = 1 / s;
    inverse *= tmp;
}

void Primitive::scale(double sx, double sy, double sz){
    Matrix tmp;
    tmp.d[0][0] = sx;
    tmp.d[1][1] = sy;
    tmp.d[2][2] = sz;
    matrix = tmp * matrix;
    tmp.d[0][0] = 1 / sx;
    tmp.d[1][1] = 1 / sy;
    tmp.d[2][2] = 1 / sz;
    inverse *= tmp;
}

void Primitive::shear(double dx, double dy, double dz, double sx, double sy, double sz){
    Matrix tmp;
    tmp.d[0][0] += sx * dx;
    tmp.d[0][1] += sy * dx;
    tmp.d[0][2] += sz * dx;
    tmp.d[1][0] += sx * dy;
    tmp.d[1][1] += sy * dy;
    tmp.d[1][2] += sz * dy;
    tmp.d[2][0] += sx * dz;
    tmp.d[2][1] += sy * dz;
    tmp.d[2][2] += sz * dz;
    matrix = tmp * matrix;
    tmp = Matrix();
    double m = 1 + sx * dx + sy * dy + sz * dz;
    tmp.d[0][0] -= sx * dx / m;
    tmp.d[0][1] -= sy * dx / m;
    tmp.d[0][2] -= sz * dx / m;
    tmp.d[1][0] -= sx * dy / m;
    tmp.d[1][1] -= sy * dy / m;
    tmp.d[1][2] -= sz * dy / m;
    tmp.d[2][0] -= sx * dz / m;
    tmp.d[2][1] -= sy * dz / m;
    tmp.d[2][2] -= sz * dz / m;
    inverse *= tmp;
}

void Primitive::transformBoundingBox(const BoundingBox &box, Point &p, double &r){
    p.set((box.x1 + box.x2) * 0.5, (box.y1 + box.y2) * 0.5, (box.z1 + box.z2) * 0.5);
    Vector v1 = Point(box.x1, box.y1, box.z1) - p;
    Vector v2 = Point(box.x1, box.y2, box.z1) - p;
    Vector v3 = Point(box.x2, box.y1, box.z1) - p;
    Vector v4 = Point(box.x2, box.y2, box.z1) - p;
    double t;
    r = 0;
    inverse.operatePoint(p);
    inverse.operateVector(v1);
    inverse.operateVector(v2);
    inverse.operateVector(v3);
    inverse.operateVector(v4);
    t = v1.squaredNorm();
    if (t > r)
        r = t;
    t = v2.squaredNorm();
    if (t > r)
        r = t;
    t = v3.squaredNorm();
    if (t > r)
        r = t;
    t = v4.squaredNorm();
    if (t > r)
        r = t;
    r = sqrt(r);
}

void Primitive::generateBoundingBox(){
    bBox = matrix.operatedBoundingBox(baseBoundingBox());
}
