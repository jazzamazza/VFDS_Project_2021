// Header file for adaptive threshold class for de-noising pgm images
// htciai001
// 04/10/21
#ifndef ADAPTIVETHRESHOLD_H
#define APADTIVETHRESHOLD_H
#include <vector>

namespace denoise {
    class AdaptiveThreshold{
        private:
            int dim, n_size;
        public:
            AdaptiveThreshold();
            AdaptiveThreshold(int dim, int n_size);
            ~AdaptiveThreshold();

            void execute(unsigned char *** & source, unsigned char *** & target, int depth);
            std::vector<int> getHistogram(unsigned char *** & source, int depth);

    };
}

#endif