#include "Utility/func.h"
#include "Utility/def.h"
#include <cmath>

double fresnel(const double n1, const double n2, const double ci){
    double si = sqrt(1 - ci * ci);
    double st = n1 / n2 * si;
    if (st >= 1)
        return 1;
    double ct = sqrt(1 - st * st);
    double rs = sqr((n1 * ci - n2 * ct) / (n1 * ci + n2 * ct));
    double rt = sqr((n1 * ct - n2 * ci) / (n1 * ct + n2 * ci));
    return (rs + rt) * 0.5;
}

double fresnel(const double n1, const double n2, const double ci, double &ct, double &st){
    double si = sqrt(1 - ci * ci);
    st = n1 / n2 * si;
    if (st >= 1)
        return 1;
    ct = sqrt(1 - st * st);
    double rs = sqr((n1 * ci - n2 * ct) / (n1 * ci + n2 * ct));
    double rt = sqr((n1 * ct - n2 * ci) / (n1 * ct + n2 * ci));
    return (rs + rt) * 0.5;
}

void mapToHemisphere(const double sx, const double sy, double &pu, double &pv, double &pw, const double exp){
    double cp, sp, ct, st;
    cp = cos(2 * PI * sx);
    sp = sin(2 * PI * sx);
    ct = pow(1 - sy, 1 / (exp + 1));
    st = sqrt(1 - ct * ct);
    pu = st * cp;
    pv = st * sp;
    pw = ct;
}

void mapToHemisphere(const double sx, const double sy, double &pu, double &pv, double &pw){
    double cp, sp, ct, st;
    cp = cos(2 * PI * sx);
    sp = sin(2 * PI * sx);
    st = sqrt(1 - sqr(sy));
    pu = st * cp;
    pv = st * sp;
    pw = sy;
}

void mapToSphere(const double sx, const double sy, double &pu, double &pv, double &pw){
    double cp, sp, ct, st;
    cp = cos(2 * PI * sx);
    sp = sin(2 * PI * sx);
    st = sqrt(1 - sqr(sy * 2 - 1));
    pu = st * cp;
    pv = st * sp;
    pw = sy * 2 - 1;
}
