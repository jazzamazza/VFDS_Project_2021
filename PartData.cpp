// PartData class to store information about the background of the image stack
// htciai001
// 23/08/21
#include "PartData.h"

// default constructor
imgdata::PartData::PartData(void) : imgdata::ImageDataClass(0), shape(std::vector<Pixel>()) {}

// custom constructor
imgdata::PartData::PartData(unsigned char intensity) : imgdata::ImageDataClass(intensity), shape(std::vector<Pixel>()) {}

// destructor
imgdata::PartData::~PartData() {}

const std::vector<Pixel> imgdata::PartData::getShape() const{
    return this->shape;
}