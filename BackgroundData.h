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
            BackgroundData(int dim);
            ~BackgroundData();

            int getDim();
    };
}

#endif
