// Header file for ImageDataClass
// htciai001
// 23/08/21

#ifndef IMAGEDATACLASS_H
#define IMAGEDATACLASS_H

#include <vector>

using namespace imgdata {
    class ImageDataClass {
        
        private:
            unsigned char intensity;

        public:
            ImageDataClass(void);
            ImageDataClass(unsigned char intensity);
            virtual ~ImageDataClass();

            unsigned char getIntensity();

    };
}

#endif