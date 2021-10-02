// denoising filters implementation file for capstone
// htciai001
// 02/10/21

#include "Filter.h"

imgfltr:: MedianFilter::MedianFilter() : Filter() {}

imgfltr:: MedianFilter::MedianFilter(int size) : Filter(size) {}

unsigned char imgfltr::MedianFilter::findMedian(const std::vector<unsigned char> & neighbours) {
    std::sort(neighbours.begin(), neighbours.end());
    int middle = neighbours.size()/2;

    if (neighbours.size()%2 == 0) {
        return (neighbours[middle-1] + neighbours[middle]) / 2;
    }

    else
        return neighbours[middle];
}