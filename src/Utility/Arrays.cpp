#include "Utility/Arrays.h"
#include "Utility/BoundingBox.h"
#include <cmath>

Vector operator+(const Vector &a, const Vector &b){
    return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector &Vector::operator+=(const Vector &other){
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector operator-(const Vector &a, const Vector &b){
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector &Vector::operator-=(const Vector &other){
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector operator-(const Vector &a){
    return Vector(-a.x, -a.y, -a.z);
}

Vector operator*(const Vector &a, double k){
    return Vector(a.x * k, a.y * k, a.z * k);
}

Vector operator*(double k, const Vector &a){
    return Vector(a.x * k, a.y * k, a.z * k);
}

Vector &Vector::operator*=(double k){
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

double operator*(const Vector &a, const Vector &b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector operator/(const Vector &a, double k){
    return Vector(a.x / k, a.y / k, a.z / k);
}

Vector &Vector::operator/=(double k){
    x /= k;
    y /= k;
    z /= k;
    return *this;
}

Vector operator^(const Vector &a, const Vector &b){
    return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

Vector &Vector::normalize(){
    double t = 1 / norm();
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

Vector Vector::normalized() const{
    double t = 1 / norm();
    return Vector(x * t, y * t, z * t);
}

Matrix::Matrix(double k){
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (i == j)
                d[i][j] = k;
            else
                d[i][j] = 0;
}

Matrix operator*(const Matrix &a, const Matrix &b){
    Matrix c(0);
    int i, j, k;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            for (k = 0; k < 4; k++)
                c.d[i][j] += a.d[i][k] * b.d[k][j];
    return c;
}

Matrix &Matrix::operator*=(const Matrix &other){
    *this = *this * other;
    return *this;
}

void Matrix::operatePoint(Point &p){
    double tx = d[0][0] * p.x + d[0][1] * p.y + d[0][2] * p.z + d[0][3];
    double ty = d[1][0] * p.x + d[1][1] * p.y + d[1][2] * p.z + d[1][3];
    p.z = d[2][0] * p.x + d[2][1] * p.y + d[2][2] * p.z + d[2][3];
    p.x = tx;
    p.y = ty;
}

Point Matrix::operatedPoint(const Point &p){
    return Point(d[0][0] * p.x + d[0][1] * p.y + d[0][2] * p.z + d[0][3],
                 d[1][0] * p.x + d[1][1] * p.y + d[1][2] * p.z + d[1][3],
                 d[2][0] * p.x + d[2][1] * p.y + d[2][2] * p.z + d[2][3]);
}

void Matrix::operateVector(Vector &v){
    double tx = d[0][0] * v.x + d[0][1] * v.y + d[0][2] * v.z;
    double ty = d[1][0] * v.x + d[1][1] * v.y + d[1][2] * v.z;
    v.z = d[2][0] * v.x + d[2][1] * v.y + d[2][2] * v.z;
    v.x = tx;
    v.y = ty;
}

Vector Matrix::operatedVector(const Vector &v){
    return Vector(d[0][0] * v.x + d[0][1] * v.y + d[0][2] * v.z,
                  d[1][0] * v.x + d[1][1] * v.y + d[1][2] * v.z,
                  d[2][0] * v.x + d[2][1] * v.y + d[2][2] * v.z);
}

void Matrix::operateNormal(Normal &n){
    double tx = d[0][0] * n.x + d[1][0] * n.y + d[2][0] * n.z;
    double ty = d[0][1] * n.x + d[1][1] * n.y + d[2][1] * n.z;
    n.z = d[0][2] * n.x + d[1][2] * n.y + d[2][2] * n.z;
    n.x = tx;
    n.y = ty;
    n.normalize();
}

Normal Matrix::operatedNormal(const Normal &n){
    return Normal(d[0][0] * n.x + d[1][0] * n.y + d[2][0] * n.z,
                  d[0][1] * n.x + d[1][1] * n.y + d[2][1] * n.z,
                  d[0][2] * n.x + d[1][2] * n.y + d[2][2] * n.z).normalized();
}

BoundingBox Matrix::operatedBoundingBox(const BoundingBox &box){
    BoundingBox b;
    b.extend(operatedPoint(Point(box.x1, box.y1, box.z1)));
    b.extend(operatedPoint(Point(box.x1, box.y1, box.z2)));
    b.extend(operatedPoint(Point(box.x1, box.y2, box.z1)));
    b.extend(operatedPoint(Point(box.x1, box.y2, box.z2)));
    b.extend(operatedPoint(Point(box.x2, box.y1, box.z1)));
    b.extend(operatedPoint(Point(box.x2, box.y1, box.z2)));
    b.extend(operatedPoint(Point(box.x2, box.y2, box.z1)));
    b.extend(operatedPoint(Point(box.x2, box.y2, box.z2)));
    return b;
}

RGBColor operator+(const RGBColor &a, const RGBColor &b){
    return RGBColor(a.r + b.r, a.g + b.g, a.b + b.b);
}

RGBColor &RGBColor::operator+=(const RGBColor &other){
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

RGBColor operator-(const RGBColor &a, const RGBColor &b){
    return RGBColor(a.r - b.r, a.g - b.g, a.b - b.b);
}

RGBColor &RGBColor::operator-=(const RGBColor &other){
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
}

RGBColor operator*(const RGBColor &a, double k){
    return RGBColor(a.r * k, a.g * k, a.b * k);
}

RGBColor operator*(double k, const RGBColor &a){
    return RGBColor(a.r * k, a.g * k, a.b * k);
}

RGBColor &RGBColor::operator*=(double k){
    r *= k;
    g *= k;
    b *= k;
    return *this;
}

RGBColor operator*(const RGBColor &a, const RGBColor &b){
    return RGBColor(a.r * b.r, a.g * b.g, a.b * b.b);
}

RGBColor &RGBColor::operator*=(const RGBColor &other){
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
}

RGBColor operator/(const RGBColor &a, double k){
    return RGBColor(a.r / k, a.g / k, a.b / k);
}

RGBColor &RGBColor::operator/=(double k){
    r /= k;
    g /= k;
    b /= k;
    return *this;
}

RGBColor pow(const RGBColor &a, double k){
    return RGBColor(pow(a.r, k), pow(a.g, k), pow(a.b, k));
}
