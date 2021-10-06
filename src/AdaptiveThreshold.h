// Header file for adaptive threshold class for de-noising pgm images
// htciai001
// 04/10/21
#ifndef ADAPTIVETHRESHOLD_H
#define ADAPTIVETHRESHOLD_H
#include <vector>
#include <cmath>
#include <iostream>

namespace denoise {
    class AdaptiveThreshold{
        private:
            int dim, n_size;
            // parameter to assign a weighting to the std deviation of a neighbourhood of pixels in the threshold calculation
            double sigma_s;
            // parameter to assign a weighting to the mean of a neighbourhood of pixels in the threshold calculation
            double sigma_m;
        public:
            AdaptiveThreshold();
            AdaptiveThreshold(int dim, int n_size, double sigma_s, double sigma_m);
            ~AdaptiveThreshold();

            void execute(unsigned char *** & source, unsigned char *** & target, int depth);
            std::vector<int> getHistogram(unsigned char *** & source, int depth, int col, int row, int max);
            unsigned char getThreshold(std::vector<int> & histogram, int max);
            double getMean(std::vector<int> & histogram);
            double getStdDev(double mean, std::vector<int> & histogram);

    };
}

#endif
