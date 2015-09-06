#pragma once

#include <cmath>

class BoundingBox;

struct Vector{
    double x, y, z;

    Vector(double _x = 0, double _y = 0, double _z = 0):
        x(_x), y(_y), z(_z){}
    void set(double _x, double _y, double _z)
        {x = _x; y = _y; z = _z;}
    void setNormalized(double _x, double _y, double _z)
        {set(_x, _y, _z); normalize();}
    double norm() const
        {return sqrt(x * x + y * y + z * z);}
    double squaredNorm() const
        {return x * x + y * y + z * z;}

    Vector &normalize();
    Vector normalized() const;

    Vector &operator+=(const Vector &other);
    Vector &operator-=(const Vector &other);
    Vector &operator*=(double k);
    Vector &operator/=(double k);
};

typedef Vector Point;
typedef Vector Normal;

Vector operator+(const Vector &a, const Vector &b);
Vector operator-(const Vector &a, const Vector &b);
Vector operator-(const Vector &a);
Vector operator*(const Vector &a, double k);
Vector operator*(double k, const Vector &a);
double operator*(const Vector &a, const Vector &b);
Vector operator/(const Vector &a, double k);
Vector operator^(const Vector &a, const Vector &b);

struct Matrix{
    double d[4][4];

    Matrix(double k = 1);
    Matrix &operator*=(const Matrix &other);
    void operatePoint(Point &p);
    Point operatedPoint(const Point &p);
    void operateVector(Vector &v);
    Vector operatedVector(const Vector &v);
    void operateNormal(Normal &n);
    Normal operatedNormal(const Normal &n);
    BoundingBox operatedBoundingBox(const BoundingBox &box);
};

Matrix operator*(const Matrix &a, const Matrix &b);

struct RGBColor{
    double r, g, b;

    RGBColor(double v = 0):
        r(v), g(v), b(v){}
    RGBColor(double _r, double _g, double _b):
        r(_r), g(_g), b(_b){}
    void set(double _r, double _g, double _b)
        {r = _r; g = _g; b = _b;}
    double power()
        {return r + g + b;}

    RGBColor &operator+=(const RGBColor &other);
    RGBColor &operator-=(const RGBColor &other);
    RGBColor &operator*=(double k);
    RGBColor &operator*=(const RGBColor &other);
    RGBColor &operator/=(double k);
};

RGBColor operator+(const RGBColor &a, const RGBColor &b);
RGBColor operator-(const RGBColor &a, const RGBColor &b);
RGBColor operator*(const RGBColor &a, double k);
RGBColor operator*(double k, const RGBColor &a);
RGBColor operator*(const RGBColor &a, const RGBColor &b);
RGBColor operator/(const RGBColor &a, double k);
RGBColor pow(const RGBColor &a, double k);
