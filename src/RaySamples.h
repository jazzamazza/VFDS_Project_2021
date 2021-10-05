// Header file for the RaySamples class
// htciai001
// 21/09/21

#ifndef RAYSAMPLES_H
#define RAYSAMPLES_H
#include "VolumeVisualizer.h"
#include "CTReader.h"

namespace raycst {
    class RaySamples {
        private:
            int size, steps;
        public:
            RaySamples();
            RaySamples(int sz, int st);
            ~RaySamples();

            raycst::Point3 ** buildSampleOrigins(unsigned char*** & source, VolumeVisualizer & vv, double w);
            void sampleColour(double & cout, double & cin, double ccurrent, double opacity);


    };
}

#endif