// Header file for the PartData class
// htciai001
// 23/08/21

#ifndef PARTDATA_H
#define PARTDATA_H

#include "ImageDataClass.h"
#include "Pixel.h"

namespace imgdata {
    class PartData : public ImageDataClass {
        
        private:
            std::vector<Pixel> shape;
        public:
            PartData(void);
            PartData(unsigned char intensity);
            ~PartData();

            const std::vector<Pixel> getShape();

    };
}

#endif