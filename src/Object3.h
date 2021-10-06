// Header file for 3d object class
// htciai001
// 22/09/21

#ifndef OBJECT3_H
#define OBJECT3_H

#include <cmath>
#include <iostream>

namespace raycst {
    template <typename T>
    class Object3 {
        public:
            T x, y, z;
            Object3() : x(0), y(0), z(0) {}
            Object3(T x, T y, T z) : x(x), y(y), z(z) {}
            ~Object3() {}

            Object3 operator+(const Object3 & rhs) {
                    raycst::Object3 add((this->x+rhs.x), (this->y+rhs.y), (this->z+rhs.z));
                    return add; 
            }

            const T getX() const {return this->x;}
            const T getY() const {return this->y;}
            const T getZ() const {return this->z;}

    };
}

#endif