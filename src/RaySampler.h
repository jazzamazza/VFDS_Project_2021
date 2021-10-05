// Header file for the RaySampler class
// htciai001
// 21/09/21

#ifndef RAYSAMPLER_H
#define RAYSAMPLER_H
#include "VolumeVisualizer.h"
#include "CTReader.h"

namespace raycst {
    class RaySampler {
        private:
            int size, steps;
        public:
            RaySampler();
            RaySampler(int sz, int st);
            ~RaySampler();

            raycst::Point3 ** buildSampleOrigins(unsigned char*** & source, VolumeVisualizer & vv, double w);
            void sampleColour(double & cout, double & cin, double ccurrent, double opacity);


    };
}

#endif