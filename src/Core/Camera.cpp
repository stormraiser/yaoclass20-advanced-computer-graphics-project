#include "Core/Camera.h"
#include "Utility/Arrays.h"
#include "Core/Ray.h"

void Camera::setPosition(double x, double y, double z, double lx, double ly, double lz, double ux, double uy, double uz){
    pos.set(x, y, z);
    lookDir.set(lx - x, ly - y, lz - z);
    focalDis = lookDir.norm();
    lookDir /= focalDis;
    rightDir = (lookDir ^ Vector(ux, uy, uz)).normalized();
    upDir = rightDir ^ lookDir;
}

void Camera::focus(double _focalDis){
    focalDis = _focalDis;
}

void Camera::focus(double x, double y, double z){
    focalDis = (Point(x, y, z) - pos) * lookDir;
}

void Camera::setDofEnabled(bool f){
    dofEnabled = f;
}

void Camera::setAperture(double _aperture){
    aperture = _aperture;
}
