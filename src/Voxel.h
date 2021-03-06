// Header file for the Voxel class
// htciai001
// 24/08/21

#ifndef VOXEL_H
#define VOXEL_H

#include <vector>
#include <ostream>

namespace imgdata {
    class Voxel {
        private:
            int x,y,z;
            unsigned char intensity;

        public:
            Voxel(void);
            Voxel(int x, int y, int z, unsigned char intensity);

            ~Voxel();

            Voxel(const Voxel& v);
            Voxel& operator=(const Voxel& rhs);

            Voxel(Voxel&& v);
            Voxel& operator=(Voxel&& rhs);

            const unsigned char getIntensity() const;
            const int getX() const;
            const int getY() const;
            const int getZ() const;
	    Voxel operator+(const Voxel & v);
	    bool operator>(const Voxel & v) const;
	    friend std::ostream & operator<<(std::ostream & out, const Voxel & v);
	    bool operator==(const Voxel & v) const;
	    bool touching(const imgdata::Voxel & v) const;
    };
}

#endif
