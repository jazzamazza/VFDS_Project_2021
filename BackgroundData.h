// Header file for the BackgroundData class
// htciai001
// 23/08/21

#ifndef BACKGROUNDDATA_H
#define BACKGROUNDDATA_H

#include "ImageDataClass.h"

namespace imgdata {
    class BackgroundData : public ImageDataClass {
        private:
            int dim;
        public:
            BackgroundData(void);
            BackgroundData(unsigned char intensity, int dim);
            ~BackgroundData();

            const int getDim();
    };
}

#endif
