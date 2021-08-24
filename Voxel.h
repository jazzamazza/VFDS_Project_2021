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

            Voxel(const Voxel&& v);
            Voxel& operator=(const Voxel&& rhs);

            const std::vector<int> getCoords();
            const int getX();
            const int getY();
            const int getZ();
    };
}

#endif