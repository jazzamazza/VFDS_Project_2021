#ifndef VFDSCONTROLLER_H
#define VFDSCONTROLLER_H

#include "ImageProcessor.h"
#include "Split.h"
#include "Voxel.h"
#include "Fracture.h"
#include "CTReader.h"
#include "Filter.h"

#include <string>
#include <vector>

#include <iostream>

class VFDSController
{
private:
    /* data */
    std::string headerFilePath;
    std::string dataFolderPath;
    std::string fractureFilePath;
    std::string outputFile;
    imgread::CTReader ctReader;
    std::vector<imgdata::Fracture> fractures;
    unsigned char*** imageData;

    int depth = 256;

    imgfltr::BilateralFilter<unsigned char> bf;




    //adaptive threshold stuff
    //


    //filters


    enum traversalAxis {x,y,z} axis;
    enum denoiseAlg{Median, Bilateral} denoise;//to do

    bool newDataSet=true;
    bool dataReadSuccess=false;
    bool saveEnable=false;
    bool loadEnable=false;
    bool renderingOn=false;

    //splitmerge vec fract len vec = n fracs




public:
    VFDSController(/* args */);
    ~VFDSController();

};



#endif
