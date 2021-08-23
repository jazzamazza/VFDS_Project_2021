// Parent ImageData class for storing information about the read-in image
// htciai001
// 23/08/21

#include "ImageDataClass.h"

// default constructor
imgdata::ImageDataClass::ImageDataClass(void) : intensity(0.0) {}

// custom constructor
imgdata::ImageDataClass::ImageDataClass(unsigned char intensity) : intensity(intensity) {}

// destructor
imgdata::ImageDataClass::~ImageDataClass() {}

const unsigned char imgdata::ImageDataClass::getIntensity(void) {
    return this->intensity;
}