// Header file for the VolumeVisualizer class
#ifndef VOLUMEVISUALIZER_H
#define VOLUMEVISUALIZER_H

#include "Vector3.h"
#include "Point3.h"
#include <string>

namespace raycst {

    class VolumeVisualizer {
        // Member variables which represent the center of projection (COP), UP vector and plane normal (VPN)
        private:
            int size;
            raycst::Point3 cop;
            raycst::Vector3 up, vpn;
            void setCOP(raycst::Point3 cop);
            void setVPN();

        public:
            VolumeVisualizer() : size(0), cop(raycst::Point3(0,0,0)), up(raycst::Vector3(0,0,0)), vpn(raycst::Vector3(0,0,0)) {}
            VolumeVisualizer(int size, raycst::Point3 cop, raycst::Vector3 up);
            ~VolumeVisualizer() {}

            // computes the x_product of UP and VPN
            raycst::Vector3 getAxis_1();
            // finds an orthogonal unit vector on the image plane
            raycst::Vector3 getAxis_2();

            // functions which return the plane normal and centre of projection
            raycst::Vector3 getVPN();
            raycst::Point3 getCOP();



    };
}

#endif