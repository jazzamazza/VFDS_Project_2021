// Header file for 3d object class
// htciai001
// 22/09/21

#ifndef OBJECT3_H
#define OBJECT3_H

#include <cmath>
#include <iostream>

namespace raycst {
    class Object3 {
        public:
            double x, y, z;
            Object3();
            Object3(double x, double y, double z);
            ~Object3();

            Object3 operator+(const Object3 & rhs);

            const double getX() const;
            const double getY() const;
            const double getZ() const;

    };
}

#endif