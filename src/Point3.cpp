// 3d Point class
// htciai001
// 22/09/21
#include "Point3.h"

raycst::Point3::Point3() : raycst::Object3<int>() {}

raycst::Point3::Point3(int z, int y, int x) : raycst::Object3<int>(z,y,x) {}

raycst::Point3::~Point3() {}

raycst::Point3::Point3(const raycst::Point3 & pnt) : raycst::Object3<int>(pnt.z, pnt.y,pnt.x) {}

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
    raycst::Vector3 add((this->z+rhs.getZ()), (this->y+rhs.getY()), (this->x+rhs.getX()));
    return add;
}

raycst::Point3 raycst::Point3::operator+(const raycst::Vector3 & rhs) {
    raycst::Point3 add((this->z+rhs.getZ()), (this->y+rhs.getY()), (this->x+rhs.getX()));
    return add;
}


raycst::Vector3 raycst::Point3::operator-(const raycst::Point3 & rhs) {
    raycst::Vector3 sub((this->z-rhs.getZ()), (this->y-rhs.getY()), (this->x-rhs.getX()));
    return sub;
}


raycst::Point3 raycst::Point3::operator*(int val) {
    raycst::Point3 multiply((this->z*val), (this->y*val), (this->x*val));
    return multiply;
}

raycst::Point3 raycst::Point3::operator/(const raycst::Point3 & rhs) {
    raycst::Point3 divide((this->z/rhs.getZ()), (this->y/rhs.getY()), (this->x/rhs.getX()));
    return divide;
}

raycst::Point3 raycst::Point3::absolute(void) {
    raycst::Point3 absolute(std::abs(this->z), std::abs(this->y), std::abs(this->x));
    return absolute;
}