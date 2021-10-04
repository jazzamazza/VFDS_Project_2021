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
#include "Filter.h"

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
        /*files = argv[1];
        shape = findShape(files);
        dim = findDim(files);*/
	std::string name = argv[1];
	int loc_ = name.find("_");
	std::string stringdim = name.substr(loc_-3, 3);
	dim = std::stoi(stringdim);

	std::cout << dim << std::endl;

	imgfltr::BilateralFilter<unsigned char> bf(256, 4, 0.05);

        std::cout << "CTReader start" << std::endl;
	unsigned char *** rawCube = ctr.imgread::CTReader::readPGMStack(name, dim);
        std::cout << "CTReader end" << std::endl;


        std::cout << "Filter Conver start" << std::endl;
        imgdata::Voxel*** vox = bf.toVoxel(rawCube);
        std::cout << "Filter Conver end" << std::endl;

	//func::writeRawCube("rawCube", rawCube, dim);
	//func::writeCube("originalCube", vox, dim); 

	std::cout << "Paint Background start" << std::endl;
	func::paintBackground(vox, dim, dim, dim, 150);
	std::cout << "Paint Background end" << std::endl;

//	func::writeCube("paintedCube", vox, dim);


        std::cout << "Split/Merge start" << std::endl;
        std::vector<imgdata::Fracture> frac = func::splitMerge(vox, dim, dim, dim);
        std::cout << "Split/Merge end" << std::endl;

	std::vector<imgdata::Fracture> toPrint;
	for(std::vector<imgdata::Fracture>::iterator i = frac.begin(); i != frac.end(); ++i)
	{
		if(i->getVoxels() > 50)
		{
			//std::cout << *i << std::endl;
			toPrint.push_back(*i);
		}
	}

	std::cout << toPrint.size() << std::endl;

	//testing save
	func::saveGroupFractures(toPrint, "fractures");
	std::vector<Fracture> loaded = func::loadGroupFractures("fractures");

	func::writeToPGM("og", toPrint, dim);
	func::writeToPGM("savedANDloaded", loaded, dim);


        //std::cout << "delete pgm stack" << std::endl;
        //ctr.imgread::CTReader::deletePGMStack(vox, 128); 
    }
    
    return 0;
}
