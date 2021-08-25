// CTReader class to read in a given stack of CT scan (PGM) images into a 3D array
// htciai001
// 25/08/21

#include "CTReader.h"

imgread::CTReader::CTReader(void) {}
imgread::CTReader::~CTReader() {}

std::vector< std::vector < std::vector<unsigned char[]>[]>[]> imgread::CTReader::readPGMStack(const std::string header, const int dim) {
    
    // read the PGM files in
    // iterate through the files based on their index
    for(int z = 0; z < dim; ++z) {

        //read the PGM file in, the index is appended to the filename
        std::ifstream in(header + std::to_string(z) + ".pgm", std::ios::binary);
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



    }
}


