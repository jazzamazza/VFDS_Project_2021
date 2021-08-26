// Voxel class to represent 3d image data
// htciai001
// 24/08/21

#include "Voxel.h"

// default constructor
imgdata::Voxel::Voxel(void) : coords(std::vector<int>()), intensity(0) {}
// custom constructor
imgdata::Voxel::Voxel(int x, int y, int z, unsigned char intensity) : intensity(intensity), coords(std::vector<int>()) {
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(z);
}

imgdata::Voxel::~Voxel() {}

// copy constructor
imgdata::Voxel::Voxel(const Voxel& v) : coords(v.coords), intensity(v.intensity) {}

// copy assignment operator
imgdata::Voxel& imgdata::Voxel::operator=(const imgdata::Voxel& rhs) {
    // ensure that this is not self-assignment
    if(this != &rhs) {
        this->intensity = rhs.intensity;

        if(!this->coords.empty()) {
            coords.clear();
        }

        if(!rhs.coords.empty())
            this->coords = rhs.coords;
    }

    return *this;
}

// move constructor
imgdata::Voxel::Voxel(imgdata::Voxel&& v) : coords(coords), intensity(intensity) {
    v.coords.clear();
    v.intensity = 0;
}

imgdata::Voxel& imgdata::Voxel::operator=(imgdata::Voxel&& rhs) {
    // ensure that this is not self-assignment
    if(this != &rhs) {
        this-> intensity = rhs.intensity;

        if(!this->coords.empty()) {
            this->coords.clear();
        }

        if(!rhs.coords.empty()) {
            this->coords = rhs.coords;
            rhs.coords.clear();
        }

        rhs.intensity = 0;
    }

    return *this;
}

const std::vector<int> imgdata::Voxel::getCoords() const{
    return this->coords;
}

const unsigned char imgdata::Voxel::getIntensity() const {
    return this->intensity;
}

const int imgdata::Voxel::getX() const{
    return this->coords[0];
}
const int imgdata::Voxel::getY() const{
    return this->coords[1];
}
const int imgdata::Voxel::getZ() const{
    return this->coords[2];
}
