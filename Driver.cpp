/*
Jared May
25/08/2021
VFDS DRIVER CLASS
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Split.h"
#include "Voxel.h"
#include "ImageProcessor.h"
#include "Fracture.h"
#include "CTReader.h"


int main(int argc, char* argv[])
{
    using namespace imgdata;

    imgread::CTReader ctr;
    std::string files = "";
    int dim = 0;
    std::stringstream ss;
    //get image folder name
    
    if (argc==1)
    {
        std::cout << "Please provide a folder name as an argument" << std::endl;
        return 1;
    }
    else
    {
        //./drv cross128
        files = argv[1];
        //std::cout << files[3] << std::endl;
        /*ss << files;
        std::string tmp;
        int found;
        
        while (!ss.eof()) 
        {
        /// extracting word by word from stream
        ss >> tmp;
  
        // Checking the given word is integer or not
        if (std::stringstream(tmp) >> found)
            std::cout << found << " ";
  
        // To save from space at the end of string
        tmp = "";
        }*/
        //int index = files.find
        std::cout << "CTReader start" << std::endl;
        imgdata::Voxel*** vox = ctr.imgread::CTReader::readPGMStack("cross", 128);
        std::cout << "split merge start" << std::endl;
        std::vector<imgdata::Fracture> frac = func::splitMerge(vox, 128, 128, 128);
        //std::cout << "delete pgm stack" << std::endl;
        //ctr.imgread::CTReader::deletePGMStack(vox, 128);   
    }
    
    return 0;

    //my old useless code
    /* 
    std::vector<std::string> pgm_lines;
    std::string filename = "";
    int w=0,h=0,r=0,c=0;

    if (argc==1)
    {
        std::cout << "Please input a file name" << std::endl;
        return 1;
    }
    else
    {
        filename = argv[1];
        std::ifstream in(filename);
        if(!in)
        {
            std::cout << "Couldn't open file " << filename << std::endl;
            return 1;
        }
        std::stringstream ss;
        std::string line = "";

        //PGM:Version (Magic no)
        getline(in,line);
        if (line.compare("P5")!=0)
        {
            std::cerr << "Not PGM" << std::endl;
        }
        else
        {
           std::cout << "Version: " << line << std::endl;
        }

        //Comment
        getline(in,line);
        std::cout << "Comment: " << line << std::endl;
        

        ss << in.rdbuf();

        ss >> c >> r;
        while(std::getline(in, line))
        {
            pgm_lines.push_back(line);
            std::cout << line << std::endl;
        }
        in.close();

        std::cout << pgm_lines.size() << " lines in file" << std::endl;
        
    }*/

}