// Header file for the Voxel class
// htciai001
// 24/08/21

#ifndef VOXEL_H
#define VOXEL_H

#include <vector>

namespace imgdata {
    class Voxel {
        private:
            std::vector<int> coords;
            int intensity;

        public:
            Voxel(void);
            Voxel(int x, int y, int z, int intensity);

            ~Voxel();

            Voxel(const Voxel& v);
            Voxel& operator=(const Voxel& rhs);

            Voxel(Voxel&& v);
            Voxel& operator=(Voxel&& rhs);

            const std::vector<int> getCoords() const;
            const int getX() const;
            const int getY() const;
            const int getZ() const;
    };
}

#endif