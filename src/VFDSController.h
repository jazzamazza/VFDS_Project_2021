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
    std::string headerPath="";


public:
    VFDSController(/* args */);
    ~VFDSController();

    std::string getFile();
    void loadFile(std::string path);


};



#endif
