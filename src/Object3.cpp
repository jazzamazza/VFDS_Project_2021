// 3d object class for vfds
// htciai001
// 22/09/21

#include "Object3.h"

raycst::Object3::Object3() : x(0), y(0), z(0) {}

raycst::Object3::Object3(double x, double y, double z) : x(x), y(y), z(z) {}

raycst::Object3::~Object3() {}

raycst::Object3 raycst::Object3::operator+(const raycst::Object3 & rhs) {
    raycst::Object3 add((this->x+rhs.x), (this->y+rhs.y), (this->z+rhs.z));
    return add;
}

const double raycst::Object3::getX() const{
    return this->x;
}
const double raycst::Object3::getY() const{
    return this->y;
}
const double raycst::Object3::getZ() const{
    return this->z;
}