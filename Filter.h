// denoising filter classes for capstone project
// htciai001
// 02/10/21
#ifndef FILTER_H
#define FILTER_H
#include "CTReader.h"
#include <vector>
#include <algorithm>

namespace imgfltr {
    class Filter {
        private:
            int size;
        public:
            Filter() : size (0) {}
            Filter(int size) : size(size) {}
            ~Filter() {}
            virtual void *** execute(unsigned char *** & source);
    };

    class MedianFilter : public Filter {
            public:
                MedianFilter();
                MedianFilter(int size);
                void *** execute(unsigned char *** & source);
                unsigned char findMedian(const std::vector<unsigned char> & neighbours);
    };
}

#endif