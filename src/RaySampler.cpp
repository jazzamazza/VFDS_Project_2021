// RaySampler class for vfds. Creates the 3D sample grid for projection
// htciai001
// 21/09/21

#include "RaySampler.h"

raycst::RaySampler::RaySampler() : size(0), steps(1) {}

raycst::RaySampler::RaySampler(int sz, int st) : size(sz), steps(st) {}

raycst::RaySampler::~RaySampler() {}

unsigned char ** raycst::RaySampler::sample(unsigned char*** & source, VolumeVisualizer & vv) {
    int dim = size/steps;
    // create the imaging plane of resolution 256x256
    unsigned char ** img_plane = new unsigned char * [this->size];
    for (int k = 0; k < 256; ++k) {
        img_plane[k] = new unsigned char[this->size];
    }

    // build the ray origins
    int y = 0, x = 0;
    // represents y axis traversal
    for (int i = -dim; i < (dim); ++i) {
        // represents x axis traversal
        for (int j = -(dim); j < (dim); ++j) {
            raycst::Point3 sample_point(vv.getCOP() + (vv.getAxis_1()*(i*this->steps)) + (vv.getAxis_2()*(j*this->steps)));
            //std::cout << sample_point.getX() << " " << sample_point.getY() << " " << sample_point.getZ() << std::endl;
            
            double colour = shootRay(source, vv.getVPN(), sample_point);
            
            if (colour > 255) {
                colour = 255;
            }

            //std::cout << y << " " << x << std::endl;
            img_plane[y][x] = (unsigned char)colour;


            // increment the x axis of the imaging plane
            ++x;
        }
        // increment the y axis of the imaging plane
        ++y;
        x = 0;
    }

    return img_plane;
}

double raycst::RaySampler::sampleColour(double c_in, double ccurrent) {
    double opacity = ccurrent/255;
    if (opacity > 0) {
        return c_in*(1-opacity) + ccurrent*opacity;
    }
    else
        return c_in;
}

// shoot a ray and do a backwards trace of the path, sampling each point along the way
double raycst::RaySampler::shootRay(unsigned char*** & source, raycst::Vector3 direction, raycst::Point3 & origin) {
    std::vector<raycst::Point3> ray_path;
    // build the path and truncates the ray when empty space after a voxel is detected
    // initialise the number of steps along the ray
    int k = 0;
    // checking value for truncating the ray if too much blank space is detected consecutively
    int blank = 0;
    // boolean to indicate that the ray has started to pass through data with intensity
    bool hit_data = false;
    double c_in = 0, c_out = 0;

    while(true){
        
        // exit the loop once data has been hit and sufficient blank space has been traversed
        // otherwise, exit if 3/4 of the 1D dimension of the data cube had been traversed without hitting data
        if ((hit_data && blank > 10) || (blank > this->size/2)) {
            break;
        }

        // determine the current voxel along the path
        raycst::Point3 voxel = origin + direction*(k*this->steps);
        // either retrieve its value from the data cube or assign a value of 0 if out of bounds
        if ((voxel.getX() < 0 || voxel.getX() > this->size-1) || (voxel.getY() < 0 || voxel.getY() > this->size-1) || (voxel.getZ() < 0 || voxel.getZ() > this->size-1)) {
            // increment the non-data-holding voxel counter
            ++blank;
        }
        // if the point is within the data cube
        else {
            ray_path.push_back(voxel);
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
        // increment the counter for current steps
        ++k;
        
    
    }

    // reverse iterate through the vector, accumulating the colour along the way in c_out
    if (!ray_path.empty()) {
        for (std::vector<Point3>::reverse_iterator it = ray_path.rbegin(); it != ray_path.rend(); ++it ) {
            c_out = sampleColour(c_in, source[(*it).getZ()][(*it).getY()][(*it).getX()]);
            // set future colour input to current colour output
            c_in = c_out;
        }
    }

    return c_out;
}
