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
            T z, y, x;
            Object3() : z(0), y(0), x(0) {}
            Object3(T z, T y, T x) : z(z), y(y), x(x) {}
            ~Object3() {}

            Object3 operator+(const Object3 & rhs) {
                raycst::Object3<T> add((this->z+rhs.z), (this->y+rhs.y), (this->x+rhs.x));
                return add; 
            }

            const T getX() const {return this->x;}
            const T getY() const {return this->y;}
            const T getZ() const {return this->z;}

    };
}

#endif