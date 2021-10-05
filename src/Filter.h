// denoising filter classes for capstone project
// htciai001
// 02/10/21
#ifndef FILTER_H
#define FILTER_H
#include "Voxel.h"
#include "ImageProcessor.h"
#include <vector>
#include <cmath>
#include <algorithm>

namespace imgfltr {
    template <typename T>
    class Filter {
        public:
            // length of one side of the data cube
            int size;
            Filter() : size (0) {}
            Filter(int size) : size(size) {}
            ~Filter() {}

            virtual T *** execute(T *** & source, int n_size) = 0;

            // convert a 3d array of faw pointer to a 3d array of Voxel class objects
            imgdata::Voxel *** toVoxel(T *** & source) {
                // declare a dynamic 3D array of Voxel objects
                
                imgdata::Voxel *** v_arr = new imgdata::Voxel ** [size];
                for (int i = 0; i < this->size; ++i) {
                    // initialize the 2D component size
                    v_arr[i] = new imgdata::Voxel * [size];
                    for (int j = 0; j < this->size; ++j) {
                        // initialize the 1D component size
                        v_arr[i][j] = new imgdata::Voxel[size];
                    }
                }
		

                // Insert a Voxel item into the 3D array containing each coordinate point and the intensity at that point of the PGM image
                // Necessary for split and merge algorithm
                for (int depth = 0; depth < this->size; ++depth) {
                    for (int col = 0; col < this->size; ++col) {
                        for (int row = 0; row < this->size; ++row){
                            v_arr[depth][col][row] = imgdata::Voxel(col, row, depth, std::move(source[depth][col][row]));
			}
                    }
                }
                return v_arr;
            }

    };

    template <typename T>
    class MedianFilter : public Filter<T> {
            public:
                MedianFilter()  : Filter<T>() {}
                MedianFilter(int size) : Filter<T>(size) {}
                ~MedianFilter() {}

                // implementation of the MedianFilter class

                // finds the median of a vector of the templated type given the neighbouring pixels
                T findMedian(std::vector<T> & neighbours) {
                    std::sort(neighbours.begin(), neighbours.end());
                    int middle = floor(neighbours.size()/2);

                    if (neighbours.size()%2 == 0) {
                        return (neighbours[middle-1] + neighbours[middle]) / 2;
                    }

                    else
                        return neighbours[middle];                    
                }


                // finds the pixels neighbouring the source pixel and gathers them in a standard vector
                std::vector<T> collectNeighbours(T *** & source, int n_size, int depth, int col, int row) {
                    int half_n = floor(n_size/2);
                    std::vector<T> neighbours;
                    for (int i = col - half_n; i < col + half_n + 1; ++i) {
                        for (int j = row - half_n; j < row + half_n + 1; ++j) {
                            if ((i < 0 || i >= this->size) || (j < 0 || j >= this-> size)) {
                                // pads the outer pixels with 0s if at a boundary (no neighbour in that direction)
                                // we expect the outermost background pixels to be of this value anyway, so this should not skew the median data values drastically
                                neighbours.push_back(0);
                            }
                            else {
                                neighbours.push_back(source[depth][i][j]);
                            }
                                
                        }
                    }
                    return neighbours;
                }

                // executes the filtering method on a source 3d array given the intended size of the neighbourhood
                // accept input for n_size in the format: n_size = n_sizexn_size or (n_size^2)
                T *** execute(T *** & source, int n_size) {
                    T *** src_cpy = source;
                    // outermost loop: z-axis
                    for(int i = 0; i < this->size; ++i) {
                        for(int j = 0; j < this-> size; ++j) {
                            for(int k = 0; k < this->size; ++k) {
                                // collect the neighbours of the currently iterated datapoint
                                std::vector<T> neighbours = collectNeighbours(source, n_size, i, j, k);
                                // pass this vector to a function to detect the median
                                // replace the value in src_cpy
                                src_cpy[i][j][k] = findMedian(neighbours);
                            }
                        }
                    }

                    return src_cpy;
                }
    };

    template <typename T>
    class BilateralFilter : public Filter<T> {
        private:
            double sigma_q, sigma_r;
        public:
            BilateralFilter() : Filter<T>(), sigma_q(0), sigma_r(0) {}
            BilateralFilter(int size, double sq, double sr) : Filter<T>(size), sigma_q(sq), sigma_r(sr) {}
            ~BilateralFilter() {}

            T *** execute(T *** & source, int n_size) {
                T *** src_filtered = source;
                // outermost loop: z-axis
                for(int i = 0; i < this->size; ++i) {
                    for(int j = 0; j < this-> size; ++j) {
                        for(int k = 0; k < this->size; ++k) {
                            src_filtered[i][j][k] = (unsigned char)bilateralWeightFunction(source, n_size, i, j, k);
                        }
                    }
                }
                return src_filtered;
            }

            double bilateralWeightFunction(T *** & source, int n_size, int depth, int col, int row) {
                
                T neighbour;
                double gauss_r, gauss_s, wr, ws;

                int half_n = floor(n_size/2);

                for (int i = col - half_n; i < col + half_n + 1; ++i) {
                    for (int j = row - half_n; j < row + half_n + 1; ++j) {
                        if ((i < 0 || i >= this->size) || (j < 0 || j >= this-> size)) {
                            // pads the outer pixels with 0s if at a boundary (no neighbour in that direction)
                            // we expect the outermost background pixels to be of this value anyway, so this should not skew the median data values drastically
                            neighbour = 0;
                        }
                        else {
                            neighbour = source[depth][i][j];
                        }

                        // execute both gaussian kernel operations
                        domainKernel(neighbour, depth, col, row, i, j, gauss_r, wr);
                        spacialKernel(source, neighbour, depth, col, row, i, j, gauss_s, ws);                                
                    }
                }

                // return the gaussian value for the pixel and normalise with the combined weights
                return (gauss_r*gauss_s)/(wr*ws);
            }

            void domainKernel(T neighbour, int depth, int col, int row, int i, int j, double & gauss_r, double & wr) {
                // determine the gaussian filter weight
                double g = std::exp(-(std::pow((i),2) + std::pow((j),2)) / (2 * std::pow(this->sigma_r,2)));
                // accumulate the filtered output
                gauss_r += g * neighbour;
                // accumulate the weight for normalization of the final accumulated gaussian
                wr += g;
            }

            void spacialKernel(T *** & source, T neighbour, int depth, int col, int row, int i, int j, double & gauss_s, double & ws) {
                // determine the distance between the pixel intensities
                double d = source[depth][col][row] - neighbour;
                // determine the gaussian filter weight
                double g = std::exp(-(std::pow(d,2)) / (2 * std::pow(this->sigma_q,2)));
                // accumulate the filtered output
                gauss_s += g * neighbour;
                // accumulate the weight for normalization of the final accumulated gaussian
                ws += g;
            }

    };
}

#endif
