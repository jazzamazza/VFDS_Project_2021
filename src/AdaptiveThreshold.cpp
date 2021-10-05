// Implementation file for adaptive threshold class for de-noising pgm images
// htciai001
// 04/10/21

#include "AdaptiveThreshold.h"
#include <iostream>

denoise::AdaptiveThreshold::AdaptiveThreshold() : dim(0) {}
denoise::AdaptiveThreshold::AdaptiveThreshold(int dim) : dim(dim) {}
denoise::AdaptiveThreshold::~AdaptiveThreshold() {}

// returns a histogram containing the frequency of each pixel intensity across the source image
std::vector<int> denoise::AdaptiveThreshold::getHistogram(unsigned char *** & source, int depth, int max) {
    std::vector<int> histogram(max+1);
    for (int i = 0; i < this->dim; ++i) {
        for (int j = 0; j < this->dim; ++j) {
            histogram.at((int)source[depth][i][j]) += 1;
        }
    }
    return histogram;
}

// determine the weighted mean of a pixel category
void denoise::AdaptiveThreshold::getMean(int start, int end, double & mean, std::vector<int> & histogram) {
    // a count of the pixel values present in the classified category (bg, obj)
    int n = 0;
    for(int i = start; i < end; ++i) {
        mean += i*histogram.at(i);
        n += histogram.at(i);
    }

    mean = mean/n;
}

unsigned char denoise::AdaptiveThreshold::getThreshold(std::vector<int> & histogram, int max) {
    // Initialise the starting threshold T0 as the weighted average of the pixel intensities, based on their appearance in the hisogram
    double threshold = 0;

    for (int i = 0; i < max; ++i) {
        threshold += i*histogram.at(i);
    }
    threshold = threshold/(this->dim*this->dim);

    // define a background and object identification vector
    double threshold_next = 0;

    // loop until the threshold converges (it no longer changes between iterations)
    while(threshold_next != threshold) {
        threshold = threshold_next;
        // reset the mean values for the background and object pixels (classified by the threshold)
        double o_mean = 0, b_mean = 0;

        getMean(0, threshold+1, b_mean, histogram);
        getMean(threshold+1, max, o_mean, histogram);

        threshold_next = (b_mean + o_mean)/2;
    }

    return threshold;

}

void denoise::AdaptiveThreshold::execute(unsigned char *** & source, unsigned char *** & target, int depth) {
    unsigned char *** src_copy = source;
    // get the max pixel value in the image
    int max = 0;
    for (int k = 0; k < dim; ++k) {
        for (int l = 0; l < dim; ++l) {
            if (source[depth][k][l] > max)
                max = source[depth][k][l];
        }
    }

    std::vector<int> histogram = getHistogram(src_copy, depth, max);
    unsigned char threshold = getThreshold(histogram, max);
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            if (source[depth][i][j] < threshold) {
                target[depth][i][j] = 0;
            }
            else {
                target[depth][i][j] = max;
            }
        }
    }
}   