// VolumeVisualizer class for the capstone assessment
#include "VolumeVisualizer.h"
#include <math.h>

raycst::VolumeVisualizer::VolumeVisualizer() : size(0), cop(raycst::Point3(0,0,0)), up(raycst::Vector3(0,0,0)), vpn(raycst::Vector3(0,0,0)) {}

raycst::VolumeVisualizer::VolumeVisualizer(int size) : size(size) , up(raycst::Vector3(0,1,0)) {
    // set the centre of projection to the centre of the x and y planes and a length + 0.3*(radius of sphere surrounding the data cube) away from the data cube
    int r = std::sqrt(2*std::pow(this->size/2, 2));
    int z_start = size + r*0.3;
    setCOP(size/2, size/2, z_start);
    setVPN();
    setUP();
}

void raycst::VolumeVisualizer::setVPN() {
    // get point at the centre of the 3d
    raycst::Point3 centre((this->size/2), (this->size/2), (this->size/2));
    // determine the vector from COP to the centre of the stack (the attention point)
    // To get a vector between two points we subtract the start from the terminal point (AP-COP)
    vpn = centre-cop;
    // normalize to get the viewing plane
    vpn.normalize();
}

void raycst::VolumeVisualizer::setUP() {
    // simply get the 2nd axis of a parallel plane
    this->up = getAxis_2();
}

void raycst::VolumeVisualizer::setCOP(int x, int y, int z) {
    // set the new centre of projection
    this->cop = raycst::Point3(x,y,z);
    // calculate and set the new plane normal
    setVPN();
}

// computes the x_product of UP and VPN
raycst::Vector3 raycst::VolumeVisualizer::getAxis_1() {
    raycst::Vector3 axis_1 = this->up.cross_product(vpn);
    axis_1.normalize();
    return axis_1;
}
// finds an orthogonal unit vector on the image plane
raycst::Vector3 raycst::VolumeVisualizer::getAxis_2() {
    raycst::Vector3 axis_2 = this->vpn.cross_product(getAxis_1());
    axis_2.normalize();
    return axis_2;
}

raycst::Vector3 raycst::VolumeVisualizer::getVPN() {
    return this->vpn;
}

raycst::Point3 raycst::VolumeVisualizer::getCOP() {
    return this->cop;
}

// allows the COP to move in 1 of 4 directions in a spherical border around the data cube
// 0: UP (+y axis), 1: DOWN (-y axis), 2: RIGHT, 3: LEFT
void raycst::VolumeVisualizer::moveCOP(int dir) {
    double radius = std::sqrt(2*std::pow(this->size/2, 2));
    int nx = cop.getX(), ny = cop.getY(), nz = cop.getZ();

    if (dir == 0) 
    {
	    //up
	    ny += 10;
	    nz = 128 - std::sqrt(radius*radius - (ny - 128)*(ny-128));
	    
    }

    else if (dir == 1) 
    {
	    //left
    }

    else if (dir == 2) 
    {
	    //right
    }
    
    else if (dir == 3) 
    {
	    //down
    }

    setCOP(nz, ny, nx);
}
