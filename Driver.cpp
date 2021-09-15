/*
Jared May
25/08/2021
VFDS DRIVER CLASS
*/

//#include <fstream>
#include <iostream>
//#include <sstream>
#include <string>
#include <vector>

#include "Split.h"
#include "Voxel.h"
#include "ImageProcessor.h"
#include "Fracture.h"
#include "CTReader.h"

//find image dimension from folder name
int findDim(std::string str)
{
    int dim = 0;
    std::string tmp = "";
    //for (int i = str.length()-3; i < str.length(); i++)
    for (int i = 0; i < str.length(); i++)
    {
        if (std::isdigit(str[i]))
        {
            tmp.push_back(str[i]);
        }
    }
    dim = std::stoi(tmp);
    return(dim);
}

//find shape name from folder name
std::string findShape(std::string str)
{
    std::string tmp = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (!std::isdigit(str[i]))
        {
            tmp.push_back(str[i]);
        }   
    }
    return(tmp);
}

int main(int argc, char* argv[])
{
    using namespace imgdata;

    imgread::CTReader ctr;
    std::string files = "";
    std::string shape = "";
    int dim = 0;
    
    //get image folder name as argument
    if (argc==1)
    {
        std::cout << "Please provide a folder name as an argument" << std::endl;
        return 1;
    }
    else
    {
        files = argv[1];
        shape = findShape(files);
        dim = findDim(files);

        std::cout << "CTReader start" << std::endl;
        imgdata::Voxel*** vox = ctr.imgread::CTReader::readPGMStack(shape, dim);
        std::cout << "CTReader end" << std::endl;

	std::cout << "Paint Background start" << std::endl;
	func::paintBackground(vox, dim, dim, dim);
	std::cout << "Paint Background end" << std::endl;


        std::cout << "Split/Merge start" << std::endl;
        std::vector<imgdata::Fracture> frac = func::splitMerge(vox, dim, dim, dim);
        std::cout << "Split/Merge end" << std::endl;

	//for(std::vector<imgdata::Fracture>::iterator i = frac.begin(); i != frac.end(); ++i)
	//{
	//	std::cout << *i << std::endl;
	//}
        //std::cout << "delete pgm stack" << std::endl;
        //ctr.imgread::CTReader::deletePGMStack(vox, 128);   
    }
    
    return 0;
}
