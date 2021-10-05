// Vector3 class for capstone
// htciai001
// 15/09/21

#include "Vector3.h"

raycst::Vector3::Vector3() : raycst::Object3(0,0,0) {}

raycst::Vector3::~Vector3() {}

raycst::Vector3::Vector3(double x, double y, double z) : raycst::Object3(x,y,z) {}

raycst::Vector3::Vector3(const raycst::Vector3 & vec) : raycst::Object3(vec.x, vec.y,vec.z) {}

raycst::Vector3& raycst::Vector3::operator=(const raycst::Vector3 & rhs) {
    if(this != &rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }
    return *this;
}

// get the magnitude of a vector
double raycst::Vector3::magnitude(void) {
    return sqrt((pow(x,2)+pow(y,2)+pow(z,2)));
}

// normalize a vector
void raycst::Vector3::normalize(void) {
    double mag = this->magnitude();
    if (mag!=0) {
        this->x /= mag;
        this->y /= mag;
        this->z /= mag;
    }
}

// determine the cross product of two vectors
raycst::Vector3 raycst::Vector3::cross_product(const raycst::Vector3 & rhs) {
    // using the formula of a 3x3 matrix multiplication with top row as the 3 identity matrices: i,j,k
    raycst::Vector3 cross(((this->y*rhs.z) - (this->z*rhs.y)), ((this->z*rhs.x) - (this->x*rhs.z)), ((this->x*rhs.y)-(this->y*rhs.x)));
    return cross;
}

void raycst::Vector3::printVec3(void) {
    std::cout << "(" << this->getX() << "," << this->getY() << "," << this->getZ() << ")" << std::endl;
}

raycst::Vector3 raycst::Vector3::operator+(const raycst::Vector3 & rhs) {
    raycst::Vector3 add((this->x+rhs.x), (this->y+rhs.y), (this->z+rhs.z));
    return add;
}

raycst::Vector3 raycst::Vector3::operator*(double val) {
    raycst::Vector3 multiply((this->x*val), (this->y*val), (this->z*val));
    return multiply;
}