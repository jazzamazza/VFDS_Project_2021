// CTReader class to read in a given stack of CT scan (PGM) images into a 3D array
// htciai001
// 25/08/21

#include "CTReader.h"

imgread::CTReader::CTReader(void) {
}
imgread::CTReader::~CTReader() {}

void imgread::CTReader::setDim(std::string &hdrPath)
{
    std::ifstream in(hdrPath, std::ifstream::in);
    std::string line = "";

    do  {
    std::getline(in,line);
    } while (line.at(0)=='#');

    dim = std::stoi(line);//catch conv error
}

int imgread::CTReader::getDim(std::string& hdrPath)
{
    setDim(hdrPath);

    if (dim>0){
        return dim;
    }
    else
        return -1;
}

int imgread::CTReader::getDim()
{
    if (dim>0){
        return dim;
    }
    else
        return -1;
}

void imgread::CTReader::setDir(std::string &hdrPath)
{
    std::size_t endofpath = hdrPath.rfind("/");

    if (endofpath!=std::string::npos)
        dir = hdrPath.substr(0,endofpath);
}

std::string imgread::CTReader::getDir(std::string& hdrPath)
{
    setDir(hdrPath);
    return dir;
}

std::string imgread::CTReader::getDir()
{
    return dir;
}

// Reads a PGM stack into a dynamically allocated 3d array of Voxel objects and returns it
unsigned char *** imgread::CTReader::readPGMStack(std::string& hdrPath)
{
    std::string folderDir = getDir(hdrPath);
    int imgDim = getDim(hdrPath);

    // declare a dynamic 3D array of unsigned char
    unsigned char *** imgArr3D = new unsigned char ** [imgDim];
    for(int i = 0; i < imgDim; ++i) {
        // initialize the 2D component size
        imgArr3D[i] = new unsigned char *[imgDim];
        for (int j = 0; j < imgDim; ++j) {
            // initialize the 1D component size
            imgArr3D[i][j] = new unsigned char [imgDim];
        }
    }

    //namespace fs = std::filesystem;

    std::string filename;

    std::size_t pathLen = folderDir.length()+1;
    std::size_t fileNameLen = hdrPath.rfind('.');
    if (fileNameLen!=std::string::npos)
        filename = hdrPath.substr(pathLen,fileNameLen-pathLen);

    // read the PGM files in
    // iterate through the files based on their index
    for(int depth = 0; depth < imgDim; ++depth) {
        //read the PGM file in, the index and .pgm extension is appended to the filename
        std::string pgmFile = folderDir+"/"+filename+std::to_string(depth)+".pgm";
        std::ifstream in(pgmFile, std::ios::binary);
        std::string line = "";

        //check if file is PGM from opening line
        std::getline(in, line);
        if (!(line == "P5"))
            std::cerr << "Error: input file does not match the template of a PGM" << std::endl;

        //discard all comment lines, denoted by #
        std::getline(in, line);
        if (line.at(0) == '#')
        {
            do{
                std::getline(in, line);
            }
            while (line.at(0) == '#');

        }

        //discard the rows + columns and the final "255" line
        std::getline(in, line);

        for(int rows = 0; rows < imgDim; ++rows) {
            //create a buffer to read in the pgm binary data
            char* buffer = new char[imgDim];
            in.read(buffer, imgDim);
            // Add buffer array values to the 3D arary of unsigned char
            imgArr3D[depth][rows] = (unsigned char*)buffer;
        }
        // close filestream
        in.close();

    }
    return imgArr3D;
}


// Reads a PGM stack into a dynamically allocated 3d array of Voxel objects and returns it
unsigned char *** imgread::CTReader::readPGMStack(std::string& dir, int& dim)
{
    // declare a dynamic 3D array of unsigned char
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

    //std::string path = "./images/" + dir;
    std::string path = dir;
    std::string filename;

    // determine whether there is a header file present in the directory
    bool has_header = false;
    // iterate through the files in the specified directory within the local images directory
    for (const auto & entry : fs::directory_iterator(path)) {
    // attempt to match the header file extension with regex
        std::string filestr = entry.path().string();

        if (std::regex_search(filestr, std::regex("\\.(hdr)$"))!= 0) {
            has_header = true;
            // trim the string to reflect a pgm filename
            // start at the point in the path where the filename begins
            int pos1 = filestr.find(dir) + dir.length()+1;
            // finish at the .hdr file extension
            int pos2 = filestr.find(".hdr");
            filename = filestr.substr(pos1, pos2-pos1);
            break;
        }
    }

    if (!has_header) {
        // return some error here <----------------------------------------------------------------------------------------------------------------------
    }
    else
    {

    }

    // read the PGM files in
    // iterate through the files based on their index
    for(int depth = 0; depth < dim; ++depth) {
        //read the PGM file in, the index and .pgm extension is appended to the filename
        std::ifstream in(path+"/"+filename+std::to_string(depth)+".pgm", std::ios::binary);
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
        }
        // close filestream
        in.close();

    }
    return imgArr3D;
}

std::string imgread::CTReader::getPGM(std::string &hdrPath, const int& layer)
{
    std::string pgmFilePath="";
    std::string fileName="";
    std::string path=getDir(hdrPath);

    std::size_t pathLen = getDir(hdrPath).length()+1;
    std::size_t fileNameLen = hdrPath.rfind('.');
    if (fileNameLen!=std::string::npos)
        fileName = hdrPath.substr(pathLen,fileNameLen-pathLen);

    pgmFilePath = path+"/"+fileName+std::to_string(layer)+".pgm";

    return pgmFilePath;
}

