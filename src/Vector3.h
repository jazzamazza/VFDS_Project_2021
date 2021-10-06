// Header file for the Vector3 class for capstone assessment
// htciai001
// 15/09/21
#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>
#include "Object3.h"


namespace raycst {
    
    // forward declaration
    class Point3;

    class Vector3 : public Object3<double> {
        public:
            Vector3();
            Vector3(double x, double y, double z);
            ~Vector3();
            Vector3(const Vector3 & vec);
            Vector3& operator=(const Vector3 & rhs);

            Vector3 operator+(const Vector3 & rhs);
            Vector3 operator+(const raycst::Point3 & rhs);
            Vector3 operator-(const raycst::Point3 & rhs);
            Vector3 operator*(double val);

            double magnitude(void);
            void normalize(void);
            Vector3 cross_product(const Vector3 & rhs);
            void printVec3(void);

    };
}

#endif