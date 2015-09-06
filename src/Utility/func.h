#pragma once
#include <cstdlib>

inline double sqr(const double x){return x * x;}
inline double randReal(){return (rand() + 0.5) / (double(RAND_MAX) + 1);}
inline double min3(double a, double b, double c){return a < b ? (a < c ? a : c) : (b < c ? b : c);}
inline double max3(double a, double b, double c){return a > b ? (a > c ? a : c) : (b > c ? b : c);}
inline int dirIndex(double a, double b, double c){return (a > 0) * 4 + (b > 0) * 2 + (c > 0);}
inline int dirRevIndex(double a, double b, double c){return (a < 0) * 4 + (b < 0) * 2 + (c < 0);}
double fresnel(const double n1, const double n2, const double ci);
double fresnel(const double n1, const double n2, const double ci, double &ct, double &st);

void mapToHemisphere(const double sx, const double sy, double &pu, double &pv, double &pw, const double exp);
void mapToHemisphere(const double sx, const double sy, double &pu, double &pv, double &pw);
void mapToSphere(const double sx, const double sy, double &pu, double &pv, double &pw);
