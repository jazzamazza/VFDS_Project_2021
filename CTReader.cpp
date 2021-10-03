// CTReader class to read in a given stack of CT scan (PGM) images into a 3D array
// htciai001
// 25/08/21

#include "CTReader.h"

imgread::CTReader::CTReader(void) {}
imgread::CTReader::~CTReader() {}

// Reads a PGM stack into a dynamically allocated 3d array of Voxel objects and returns it
unsigned char *** imgread::CTReader::readPGMStack(const std::string& dir, const int& dim) {
    
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

    namespace fs = std::filesystem;

    std::string path = "./images/" + dir;
    std::string filename;
    // determine whether there is a header file present in the directory
    bool has_header = false;
    // iterate through the files in the specified directory within the local images directory
    for (const auto & entry : fs::directory_iterator(path)) {
    // attempt to match the header file extension with regex
        std::string filestr = entry.path().string();

        if (std::regex_search(filestr, std::regex("\\.(hdr)$"))!= 0) {
            has_header = true;
            int pos1 = filestr.find(dir) + dir.length()+1;
            int pos2 = filestr.find(".hdr");
            filename = filestr.substr(pos1, pos2-pos1);
            break;
        }
    }
    if (!has_header) {
        // return some error here <----------------------------------------------------------------------------------------------------------------------
    }

    // read the PGM files in
    // iterate through the files based on their index
    for(int depth = 0; depth < dim; ++depth) {
        
        //std::string filename =  + =std::to_string(depth) + ".pgm";
        //read the PGM file in, the index is appended to the filename
        std::ifstream in(path+filename+std::to_string(depth)+".pgm", std::ios::binary);
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
    ctr.readPGMStack("cross256_14_noise", 256);
}