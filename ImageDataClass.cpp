// Parent ImageData class for storing information about the read-in image
// htciai001
// 23/08/21

#include "ImageDataClass.h"

// default constructor
imgdata::ImageDataClass(void) : intensity(0.0) {}

// custom constructor
imgdata::ImageDataClass(unsigned char intensity) : intensity(intensity) {}

// destructor
imgdata::~ImageDataClass() {}

imgdata::getIntensity(void) {
    return this->intensity;
}