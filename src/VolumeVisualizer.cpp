// VolumeVisualizer class for the capstone assessment
#include "VolumeVisualizer.h"

raycst::VolumeVisualizer::VolumeVisualizer(int size, raycst::Point3 cop, raycst::Vector3 up) : size(size), cop(cop), up(up), vpn() {
    raycst::VolumeVisualizer::setVPN();
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

void raycst::VolumeVisualizer::setCOP(raycst::Point3 cop) {
    // set the new centre of projection
    this->cop = cop;
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