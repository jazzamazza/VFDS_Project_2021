// Header file for ImageDataClass
// htciai001
// 23/08/21

#ifndef IMAGEDATACLASS_H
#define IMAGEDATACLASS_H

#include <vector>

namespace imgdata {
    class ImageDataClass {
        
        private:
            unsigned char intensity;

        public:
            ImageDataClass(void);
            ImageDataClass(unsigned char intensity);
            virtual ~ImageDataClass();

            const unsigned char getIntensity() const;

    };
}

#endif