// Header file for adaptive threshold class for de-noising pgm images
// htciai001
// 04/10/21
#ifndef ADAPTIVETHRESHOLD_H
#define APADTIVETHRESHOLD_H
#include <vector>

namespace denoise {
    class AdaptiveThreshold{
        private:
            int dim;
        public:
            AdaptiveThreshold();
            AdaptiveThreshold(int dim);
            ~AdaptiveThreshold();

            void execute(unsigned char *** & source, unsigned char *** & target, int depth);
            std::vector<int> getHistogram(unsigned char *** & source, int depth);
            unsigned char getThreshold(std::vector<int> & histogram);
            void getMean(int start, int end, double & mean, std::vector<int> & histogram);
            void classify(double threshold, std::vector<int> & obj, std::vector<int> & bg);

    };
}

#endif