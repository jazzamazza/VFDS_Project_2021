// Header file for the Point3 class for capstone assessment
// htciai001
// 22/09/21

#ifndef POINT3_H
#define POINT3_H
#include "Object3.h"
#include "Vector3.h"

namespace raycst {
    class Point3 : public Object3<int> {
        public:
            Point3();
            Point3(int x, int y, int z);
            ~Point3();
            
            Point3(const Point3 & vec);
            Point3& operator=(const Point3 & rhs);


            Vector3 operator+(const Point3 & rhs);
            Point3 operator+(const raycst::Vector3& rhs);
            Vector3 operator-(const Point3 & rhs);
            Point3 operator*(int val);
            Point3 operator/(const Point3 & rhs);

            Point3 absolute(void);

    };
}

#endif
