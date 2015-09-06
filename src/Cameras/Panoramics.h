#pragma once

#include "Cameras/Panoramic.h"

class EquirectangularPanoramic: public Panoramic{
protected:
    bool getAngle(double r, double &ang);
};

class MercatorPanoramic: public Panoramic{
protected:
    bool getAngle(double r, double &ang);
};

class BraunPanoramic: public Panoramic{
protected:
    bool getAngle(double r, double &ang);
};

class CylindricalEqualAreaPanoramic: public Panoramic{
protected:
    bool getAngle(double r, double &ang);
};
