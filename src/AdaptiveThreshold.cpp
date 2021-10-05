// Implementation file for adaptive threshold class for de-noising pgm images
// htciai001
// 04/10/21

#include "AdaptiveThreshold.h"

denoise::AdaptiveThreshold::AdaptiveThreshold() : dim(0), n_size(0), sigma_s(0), sigma_m(0) {}
denoise::AdaptiveThreshold::AdaptiveThreshold(int dim, int n_size, double sigma_s, double sigma_m) : dim(dim), n_size(n_size), sigma_s(sigma_s), sigma_m(sigma_m) {}
denoise::AdaptiveThreshold::~AdaptiveThreshold() {}

// returns a histogram containing the frequency of each pixel intensity across the source image
std::vector<int> denoise::AdaptiveThreshold::getHistogram(unsigned char *** & source, int depth, int col, int row, int max) {
    std::vector<int> histogram(max+1);
    int half_n = std::floor(this->n_size/2);
    for (int i = -half_n; i < half_n+1; ++i) {
        for (int j = -half_n; j < half_n+1; ++j) {
            histogram.at((int)source[depth][i+col][j+row]) += 1;
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

// determine an adaptive threshold via successive refinement of the peak positions
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
    // get the total cumulative value of the dataset and max pixel value in the image
    int max = 0;
    double total = 0;

    for (int k = 0; k < dim; ++k) {
        for (int l = 0; l < dim; ++l) {
            // accumulate the total
            total += source[depth][k][l];
            if (source[depth][k][l] > max)
                max = source[depth][k][l];
        }
    }
    

    //calculate population mean
    double mean = total/(dim*dim);
    double var = 0;

    // calculate the global variance for the dataset and normailize the value
    for (int y = 0; y < dim; ++y) {
        for (int x = 0; x < dim; ++x) {
            var += std::pow(((double)source[depth][y][x]-mean), 2);
        }
    }
    var = var/std::pow(dim,2);

    // if the variance across the entire dataset is below some acceptible value
    // recognise as a noisy image with no part data
    if(var < 100) {
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                // set all pixels to 0 rather than thresholding
                target[depth][i][j] = 0;
            }
        }
        return;
    }

    // new code using local histograms over neighbourhoods of pixels
    // iterate over 2d image coordinates
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            
        }
    }

    // older code using a global histogram
    /*
    std::vector<int> histogram = getHistogram(src_copy, depth, max);
    unsigned char threshold = getThreshold(histogram, max);
    
    // employ threshold across the dataset
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
    */
}   