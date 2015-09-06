#pragma once

#include "Cameras/Fisheye.h"

class EquidistantFisheye: public Fisheye{
protected:
    bool getAngle(double r, double &ang);
};

class StereographicFisheye: public Fisheye{
protected:
    bool getAngle(double r, double &ang);
};

class EqualAreaFisheye: public Fisheye{
protected:
    bool getAngle(double r, double &ang);
};

class OrthographicFisheye: public Fisheye{
protected:
    bool getAngle(double r, double &ang);
};
