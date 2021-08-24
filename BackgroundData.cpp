// ImageData class to store information about the background of the image stack
// htciai001
// 23/08/21

#include "BackgroundData.h"

// default constructor
imgdata::BackgroundData::BackgroundData(void) : imgdata::ImageClassData::ImageClassData(), dim(0) {}

// custom constructor
imgdata::BackgroundData::BackgroundData(unsigned char intensity, int dim) : ImageClassData(intensity), dim(dim) {}

imgdata::BackgroundData::~BackgroundData() {}

const int BackgroundData::BackgroundData::getDim() {
    return this->dim;
}