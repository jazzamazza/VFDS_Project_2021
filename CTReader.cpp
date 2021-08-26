// CTReader class to read in a given stack of CT scan (PGM) images into a 3D array
// htciai001
// 25/08/21

#include "CTReader.h"

imgread::CTReader::CTReader(void) {}
imgread::CTReader::~CTReader() {}

// Reads a PGM stack into a dynamically allocated 3d array of Voxel objects and returns it
imgdata::Voxel*** imgread::CTReader::readPGMStack(const std::string& header, const int& dim) {
    
    // declare a dynamic 3D array of Voxels
    imgdata::Voxel*** imgArr3D = new imgdata::Voxel**[dim];
    
    for(int i = 0; i < dim; ++i) {
        // initialize the 2D component size
        imgArr3D[i] = new imgdata::Voxel*[dim];
        for (int j = 0; j < dim; ++j) {
            // initialize the 1D component size
            imgArr3D[i][j] = new imgdata::Voxel[dim];
        }
    }

    // read the PGM files in
    // iterate through the files based on their index
    for(int depth = 0; depth < dim; ++depth) {
        
        // this treats the CT location as a directory with the name template: [shape][dim]
        std::string filepath = header+std::to_string(dim);
        std::string filename = header + std::to_string(depth) + ".pgm";
        //read the PGM file in, the index is appended to the filename
        std::ifstream in(filepath+"/"+filename, std::ios::binary);
        std::string line = "";

        //check if file is PGM from opening line
        std::getline(in, line);
        if (!(line == "P5"))
            std::cerr << "Error: input file does not match the template of a PGM" << std::endl;

        //discard all comment lines, denoted by #
        std::getline(in, line);
        if (line.at(0) == '#')
        {
            while (line.at(0) == '#')
                std::getline(in, line);
        }

        //discard the rows + columns and the final "255" line
        std::getline(in, line);
        std::getline(in, line);

        for(int cols = 0; cols < dim; ++cols) {
            //create a buffer to read in the pgm binary data
            char* buffer = new char[dim];
            in.read(buffer, dim);

            for(int rows = 0; rows < dim; ++rows) {
                // Insert a Voxel item into the 3D array containing each coordinate point and the intensity at that point of the PGM image
                // Necessary for split and merge algorithm
                imgArr3D[depth][cols][rows] = imgdata::Voxel(rows, cols, depth, (unsigned char)buffer[rows]);
            }
            // delete the dynamically allocated buffer
            delete[] buffer;
        }
        // close filestream
        in.close();

    }

    return imgArr3D;
}

// iteratively deletes the 3D Voxel array
void imgread::CTReader::deletePGMStack(imgdata::Voxel***& imgArr3D, int dim) {
    for(int i=0; i < dim; ++i) {
        for(int j=0; j < dim; ++j) {
            delete[] imgArr3D[i][j];
        }
        delete[] imgArr3D[i];
    }
    delete[] imgArr3D;
}

