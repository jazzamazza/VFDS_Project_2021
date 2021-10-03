// denoising filters implementation file for capstone
// htciai001
// 02/10/21

#include "Filter.h"

// implementation of the MedianFilter class
template <typename T>
imgfltr:: MedianFilter<T>::MedianFilter() : Filter<T>() {}

template <typename T>
imgfltr::MedianFilter<T>::MedianFilter(int size) : Filter<T>(size) {}

// finds the median of a vector of the templated type
template <typename T>
T imgfltr::MedianFilter<T>::findMedian(const std::vector<T> & neighbours) {
    std::sort(neighbours.begin(), neighbours.end());
    int middle = floor(neighbours.size()/2);

    if (neighbours.size()%2 == 0) {
        return (neighbours[middle-1] + neighbours[middle]) / 2;
    }

    else
        return neighbours[middle];
}

template <typename T>
T *** imgfltr::MedianFilter::execute(T *** & source) {
    
}
