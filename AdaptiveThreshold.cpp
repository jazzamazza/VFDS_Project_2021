// Implementation file for adaptive threshold class for de-noising pgm images
// htciai001
// 04/10/21

#include "AdaptiveThreshold.h"

denoise::AdaptiveThreshold::AdaptiveThreshold() : dim(0), n_size(0) {}
denoise::AdaptiveThreshold::AdaptiveThreshold(int dim, int n_size) : dim(dim), n_size(n_size) {}
denoise::AdaptiveThreshold::~AdaptiveThreshold() {}


std::vector<int> denoise::AdaptiveThreshold::getHistogram(unsigned char *** & source, int depth) {
    std::vector<int> histogram(256);
    for (int i = 0; i < this->dim; ++i) {
        for (int j = 0; j < this->dim; ++j) {
            histogram.at((int)source[depth][i][j]) += 1;
        }
    }
    return histogram;
}

int denoise::AdaptiveThreshold::numEntries(std::vector<int> histogram) {
    int total = 0;
    std::vector<int>::iterator it;
    for (it = histogram.begin(); it != histogram.end(); ++it) {
        total += *it;
    }
    return total;
}

unsigned char denoise::AdaptiveThreshold::getThreshold(unsigned char *** & source, int depth, vector<int> histogram) {
    // Initialise the starting threshold T0 as the weighted average of the pixel intensities, based on their appearance in the hisogram
    double threshold;
    for (int i = 0; i < 256; ++i) {
        threshold += i*histogram.at(i);
    }
    threshold = threshold/(size*size);


    double threshold_next = 0;

    // while the 
    while(threshold_next != threshold)


}

void denoise::AdaptiveThreshold::execute(unsigned char *** & source, unsigned char *** & target, int depth) {
    unsigned char *** src_copy = source;
    std::vector<int> histogram = getHistogram(src_copy, depth);
    


}   