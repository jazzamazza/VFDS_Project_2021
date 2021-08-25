// ImageData class to store information about the background of the image stack
// htciai001
// 23/08/21

#include "BackgroundData.h"

// default constructor
imgdata::BackgroundData::BackgroundData(void) : imgdata::ImageDataClass(), dim(0) {}

// custom constructor
imgdata::BackgroundData::BackgroundData(unsigned char intensity, int dim) : imgdata::ImageDataClass(intensity), dim(dim) {}

// destructor
imgdata::BackgroundData::~BackgroundData() {}

const int imgdata::BackgroundData::BackgroundData::getDim() {
    return this->dim;
}