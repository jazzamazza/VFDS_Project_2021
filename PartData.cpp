// PartData class to store information about the background of the image stack
// htciai001
// 23/08/21
#include "PartData.h"

// default constructor
imgdata::PartData::PartData(void) : imgdata::ImageDataClass(0), shape(std::vector<imgdata::Voxel>()) {}

// custom constructor
imgdata::PartData::PartData(unsigned char intensity) : imgdata::ImageDataClass(intensity), shape(std::vector<Voxel>()) {}

// destructor
imgdata::PartData::~PartData() {}

const std::vector<imgdata::Voxel> imgdata::PartData::getShape() const{
    return this->shape;
}