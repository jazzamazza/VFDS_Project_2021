// RaySampler class for vfds. Creates the 3D sample grid for projection
// htciai001
// 21/09/21

#include "RaySampler.h"

raycst::RaySampler::RaySampler() : size(0), steps(1) {}

raycst::RaySampler::RaySampler(int sz, int st) : size(sz), steps(st) {}

raycst::RaySampler::~RaySampler() {}

racst::Point3 ** raycst::RaySampler::buildSampleOrigins(unsigned char*** & source, VolumeVisualizer & vv, double w) {
    double dim = size/steps;
    // represents y axis traversal
    for (int i = -dim/2; i < (dim/2)+1; ++i) {
        // represents x axis traversal
        for (int j = -dim/2; j < (dim/2)+1; ++j) {
            raycst::Point3 samplePoint(q + (vv.getAxis_1()*(i)) + (vv.getAxis_2()*(j)));
            samplePoint = samplePoint.round();
            std::cout << samplePoint.getX() << " " << samplePoint.getY() << " " << samplePoint.getZ() << std::endl;
            vv.getVPN().printVec3();
        }
    }
}

void raycst::RaySampler::sampleColour(double & cout, double & cin, double ccurrent, double opacity) {
    if (opacity > 0) {
        return cin*(1-opacity) + ccurrent*opacity;
    }
}


int main(void) {
    raycst::VolumeVisualizer vv(128, raycst::Point3(90,90,128), raycst::Vector3(0,1,0));
    imgread::CTReader ctr;
    unsigned char *** data = ctr.readPGMStack("cross", 128);
    raycst::RaySampler rs(128, 2);
    rs.buildSampleOrigins(data, vv, 0.3);
    return 0;
}