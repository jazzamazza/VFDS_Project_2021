// Header file for the VolumeVisualizer class
#ifndef VOLUMEVISUALIZER_H
#define VOLUMEVISUALIZER_H

#include "Vector3.h"
#include "Point3.h"
#include <string>
#include <cmath>

namespace raycst {

    class VolumeVisualizer {
        // Member variables which represent the center of projection (COP), UP vector and plane normal (VPN)
        private:
            int size;
            raycst::Point3 cop;
            // UP is a unit vector reperesenting the direction directly "up" or on the +y axis from the COP
            // the VPN is vector between the COP and centre of the data cube
            raycst::Vector3 up, vpn;
            
            void setVPN();
            void setUP();

        public:
            VolumeVisualizer();
            VolumeVisualizer(int size);
            ~VolumeVisualizer() {}

            // computes the x_product of UP and VPN
            raycst::Vector3 getAxis_1();
            // finds an orthogonal unit vector on the image plane
            raycst::Vector3 getAxis_2();

            void setCOP(int x, int y, int z);

            // functions which return the plane normal and centre of projection
            raycst::Vector3 getVPN();
            raycst::Point3 getCOP();

            // allows the COP to move in 1 of 4 directions in a spherical border around the data cube
            void moveCOP(int dir);

    };
}

#endif