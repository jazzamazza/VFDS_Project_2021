// Header file for the Point3 class for capstone assessment
// htciai001
// 22/09/21

#ifndef POINT3_H
#define POINT3_H
#include "Object3.h"
#include "Vector3.h"

namespace raycst {
    class Point3 : public Object3 {
        public:
            Point3();
            Point3(double x, double y, double z);
            ~Point3();
            
            Point3(const Point3 & vec);
            Point3& operator=(const Point3 & rhs);


            Vector3 operator+(const Point3 & rhs);
            Point3 operator+(const raycst::Vector3& rhs);
            Vector3 operator-(const Point3 & rhs);
            Point3 operator*(double val);
            Point3 operator/(const Point3 & rhs);

            Point3 absolute(void);

    };
}

#endif
