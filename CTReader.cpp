// CTReader class to read in a given stack of CT scan (PGM) images into a 3D array
// htciai001
// 25/08/21

#include "CTReader.h"

imgread::CTReader::CTReader(void) {}
imgread::CTReader::~CTReader() {}

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
    for(int z = 0; z < dim; ++z) {
        
        std::string filename = header + std::to_string(z) + ".pgm";
        //read the PGM file in, the index is appended to the filename
        std::ifstream in(filename, std::ios::binary);
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

    }
}


