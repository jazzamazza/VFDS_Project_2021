// Header file for the RaySampler class
// htciai001
// 21/09/21

#ifndef RAYSAMPLER_H
#define RAYSAMPLER_H
#include "VolumeVisualizer.h"
#include <vector>

namespace raycst {
    class RaySampler {
        private:
            int size, steps;
        public:
            RaySampler();
            RaySampler(int sz, int st);
            ~RaySampler();

            unsigned char ** sample(unsigned char*** & source, VolumeVisualizer & vv);
            double sampleColour(double c_in, double c_current);
            double shootRay(unsigned char*** & source, Vector3 direction, Point3 & origin);

    };
}

#endif