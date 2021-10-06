// Vector3 class for capstone
// htciai001
// 15/09/21

#include "Vector3.h"

raycst::Vector3::Vector3() : raycst::Object3<double>(0,0,0) {}

raycst::Vector3::~Vector3() {}

raycst::Vector3::Vector3(double z, double y, double x) : raycst::Object3<double>(z,y,x) {}

raycst::Vector3::Vector3(const raycst::Vector3 & vec) : raycst::Object3<double>(vec.z, vec.y,vec.x) {}

raycst::Vector3& raycst::Vector3::operator=(const raycst::Vector3 & rhs) {
    if(this != &rhs) {
        this->z = rhs.z;
        this->y = rhs.y;
        this->x = rhs.x;
    }
    return *this;
}

// get the magnitude of a vector
double raycst::Vector3::magnitude(void) {
    return sqrt((pow(z,2)+pow(x,2)+pow(y,2)));
}

// normalize a vector
void raycst::Vector3::normalize(void) {
    double mag = this->magnitude();
    if (mag!=0) {
        this->z /= mag;
        this->x /= mag;
        this->y /= mag;
    }
}

// determine the cross product of two vectors
raycst::Vector3 raycst::Vector3::cross_product(const raycst::Vector3 & rhs) {
    // using the formula of a 3x3 matrix multiplication with top row as the 3 identity matrices: i,j,k
    raycst::Vector3 cross(((this->y*rhs.x) - (this->x*rhs.y)), ((this->x*rhs.z) - (this->z*rhs.x)), ((this->z*rhs.y)-(this->y*rhs.z)));
    return cross;
}

void raycst::Vector3::printVec3(void) {
    std::cout << "(" << this->getZ() << "," << this->getY() << "," << this->getX() << ")" << std::endl;
}

raycst::Vector3 raycst::Vector3::operator+(const raycst::Vector3 & rhs) {
    raycst::Vector3 add((this->z+rhs.z), (this->y+rhs.y), (this->x+rhs.x));
    return add;
}

raycst::Vector3 raycst::Vector3::operator*(double val) {
    raycst::Vector3 multiply((this->z*val), (this->y*val), (this->x*val));
    return multiply;
}