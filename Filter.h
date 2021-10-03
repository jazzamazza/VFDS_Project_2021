// denoising filter classes for capstone project
// htciai001
// 02/10/21
#ifndef FILTER_H
#define FILTER_H
#include "CTReader.h"
#include "Voxel.h"
#include "ImageProcessor.h"
#include <vector>
#include <cmath>
#include <algorithm>

namespace imgfltr {
    template <typename T>
    class Filter {
        private:
            // length of one side of the data cube
            int size;
        public:
            Filter() : size (0) {}
            Filter(int size) : size(size) {}
            ~Filter() {}
            virtual T *** execute(const T *** & source, int n_size);
            imgdata::Voxel *** toVoxel(const T *** & source);

    };

    template <typename T>
    class MedianFilter : public Filter<T> {
            public:
                MedianFilter();
                MedianFilter(int size);

                T *** execute(const T *** & source, int n_size);
                std::vector<T> collectNeighbours(const T *** & source, int n_size, int depth, int col, int row);
                T findMedian(const std::vector<T> & neighbours);
    };
}

#endif