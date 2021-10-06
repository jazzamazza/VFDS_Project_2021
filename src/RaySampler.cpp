// RaySampler class for vfds. Creates the 3D sample grid for projection
// htciai001
// 21/09/21

#include "RaySampler.h"

raycst::RaySampler::RaySampler() : size(0), steps(1) {}

raycst::RaySampler::RaySampler(int sz, int st) : size(sz), steps(st) {}

raycst::RaySampler::~RaySampler() {}

unsigned char ** raycst::RaySampler::sample(unsigned char*** & source, VolumeVisualizer & vv, double w) {
    double dim = size/steps;
    // create the imaging plane of resolution 256x256
    unsigned char ** img_plane = new unsigned char * [256];
    for (int k = 0; k < 256; ++k) {
        img_plane[k] = new unsigned char[256];
    }

    // build the ray origins
    int y = 0, x = 0;
    // represents y axis traversal
    for (int i = -dim; i < dim+1; ++i) {
        // represents x axis traversal
        for (int j = -dim/2; j < (dim/2)+1; ++j) {
            raycst::Point3 sample_point(vv.getCOP() + (vv.getAxis_1()*(i)) + (vv.getAxis_2()*(j)));
            img_plane[y][x] = shootRay(source, vv.getVPN(), sample_point);
            // increment the x axis of the imaging plane
            ++x;
        }
        // increment the y axis of the imaging plane
        ++y;
    }

    return img_plane;
}

void raycst::RaySampler::sampleColour(double & cout, double & cin, double ccurrent) {
    double opacity = ccurrent/255;
    if (opacity > 0) {
        cout = cin*(1-opacity) + ccurrent*opacity;
    }
}

// shoot a ray and do a backwards trace of the path, sampling each point along the way
double raycst::RaySampler::shootRay(unsigned char*** & source, raycst::Vector3 direction, raycst::Point3 & origin) {
    std::vector<raycst::Point3> ray_path;
    // build the path and truncates the ray when empty space after a voxel is detected
    // initialise the number of steps along the ray
    int k = 0;
    int blank = 0;
    bool hit_data;
    double cin = 0, cout = 0;

    while(true){
        // exit the loop once data has been hit and sufficient blank space has been traversed
        // otherwise, exit if 3/4 of the 1D dimension of the data cube had been traversed without hitting data
        if ((hit_data && blank > 10) || (blank > this->size-(this->size/4))) {
            break;
        }

        // determine the current voxel along the path
        raycst::Point3 voxel = origin + direction*(k*this->steps);
        ray_path.push_back(voxel);
        // either retrieve its value from the data cube or assign a value of 0 if out of bounds
        if ((voxel.getY() < 0 || voxel.getX() >= this->size) || (voxel.getY() < 0 || voxel.getY() >= this->size) || (voxel.getZ() < 0 || voxel.getZ() >= this->size)) {
            // increment the non-data-holding voxel counter
            ++blank;
        }
        // if the point is within the data cube
        else {
            // increment the blank check if it has an intensity of 0
            if (source[voxel.getZ()][voxel.getY()][voxel.getX()] == 0) {
                ++blank;
            }
            // otherwise, if its the first time hitting a voxel with a non-zero value, set hit_data to true
            else {
                if (!hit_data) {
                    hit_data = true;
                }
                blank = 0;
            }
        }
    }

    // reverse iterate through the vector, accumulating the colour along the way
    for (std::vector<Point3>::reverse_iterator it = ray_path.rbegin(); it != ray_path.rend(); ++it ) {
        sampleColour(cout, cin, source[(*it).getZ()][(*it).getY()][(*it).getX()]);
    }
    return cout;
}
