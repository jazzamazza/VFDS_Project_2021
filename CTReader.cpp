// CTReader class to read in a given stack of CT scan (PGM) images into a 3D array
// htciai001
// 25/08/21

#include "CTReader.h"

imgread::CTReader::CTReader(void) {}
imgread::CTReader::~CTReader() {}

// Reads a PGM stack into a dynamically allocated 3d array of Voxel objects and returns it
unsigned char *** imgread::CTReader::readPGMStack(const std::string& header, const int& dim, bool noise) {
    
    // declare a dynamic 3D array of Voxels
    unsigned char *** imgArr3D = new unsigned char ** [dim];
    
    for(int i = 0; i < dim; ++i) {
        // initialize the 2D component size
        imgArr3D[i] = new unsigned char *[dim];
        for (int j = 0; j < dim; ++j) {
            // initialize the 1D component size
            imgArr3D[i][j] = new unsigned char [dim];
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

        for(int rows = 0; rows < dim; ++rows) {
            //create a buffer to read in the pgm binary data
            char* buffer = new char[dim];
            in.read(buffer, dim);
            // Add buffer array values to the 3D arary of unsigned char
            imgArr3D[depth][rows] = (unsigned char*)buffer;
            // delete the dynamically allocated buffer
            delete[] buffer;
        }
        // close filestream
        in.close();

    }

    return imgArr3D;
}

int main(void) {
    imgread::CTReader ctr;

}