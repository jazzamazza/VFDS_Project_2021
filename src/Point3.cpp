// 3d Point class
// htciai001
// 22/09/21
#include "Point3.h"

raycst::Point3::Point3() : raycst::Object3<int>() {}

raycst::Point3::Point3(int x, int y, int z) : raycst::Object3<int>(x,y,z) {}

raycst::Point3::~Point3() {}

raycst::Point3::Point3(const raycst::Point3 & pnt) : raycst::Object3<int>(pnt.x, pnt.y,pnt.z) {}

raycst::Point3& raycst::Point3::operator=(const raycst::Point3 & rhs) {
    if(this != &rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }
    return *this;
}

// Addition and subtraction operators return the vector that forms between the two points
raycst::Vector3 raycst::Point3::operator+(const raycst::Point3 & rhs) {
    raycst::Vector3 add((this->x+rhs.getX()), (this->y+rhs.getY()), (this->z+rhs.getZ()));
    return add;
}

raycst::Point3 raycst::Point3::operator+(const raycst::Vector3 & rhs) {
    raycst::Point3 add((this->x+rhs.getX()), (this->y+rhs.getY()), (this->z+rhs.getZ()));
    return add;
}


raycst::Vector3 raycst::Point3::operator-(const raycst::Point3 & rhs) {
    raycst::Vector3 sub((this->x-rhs.getX()), (this->y-rhs.getY()), (this->z-rhs.getZ()));
    return sub;
}


raycst::Point3 raycst::Point3::operator*(int val) {
    raycst::Point3 multiply((this->x*val), (this->y*val), (this->z*val));
    return multiply;
}

raycst::Point3 raycst::Point3::operator/(const raycst::Point3 & rhs) {
    raycst::Point3 divide((this->x/rhs.getX()), (this->y/rhs.getY()), (this->z/rhs.getZ()));
    return divide;
}

raycst::Point3 raycst::Point3::absolute(void) {
    raycst::Point3 absolute(std::abs(this->x), std::abs(this->y), std::abs(this->z));
    return absolute;
}