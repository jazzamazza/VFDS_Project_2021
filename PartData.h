// Header file for the PartData class
// htciai001
// 23/08/21

#ifndef PARTDATA_H
#define PARTDATA_H

#include "ImageDataClass.h"
#include "Voxel.h"

namespace imgdata {
    class PartData : public ImageDataClass {
        
        private:
            std::vector<imgdata::Voxel> shape;
        public:
            PartData(void);
            PartData(unsigned char intensity, std::vector<imgdata::Voxel> shape);
            ~PartData();

            const std::vector<imgdata::Voxel> getShape() const;

    };
}

#endif