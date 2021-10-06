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


int main(int argc, char* argv[])
{
    using namespace imgdata;
    using namespace imgpro;
    imgread::CTReader ctr;
    std::string files = "";
    std::string shape = "";
    
    //get image folder name as argument
    if (argc==1)
    {
        std::cout << "Please provide path to header as an argument" << std::endl;
        return 1;
    }
    else
    {
        files = argv[1];

        std::cout << "CTReader start" << std::endl;
        unsigned char*** pgms = ctr.imgread::CTReader::readPGMStack(files);
        std::cout << "CTReader end" << std::endl;

    	int dim = ctr.getDim(files);



	func::writeRawCube("FirstTopView", pgms, dim);

	pgms = func::transform(pgms, dim, "x");

	pgms = func::transform(pgms, dim, "x");

	func::writeRawCube("frontView", pgms, dim);


/*
	std::cout << "Converting to Voxels start" << std::endl;
	Voxel *** vox = func::toVoxels(pgms, dim);
	std::cout << "Convert to Voxels end" << std::endl;

	//Split s(vox, dim, dim, dim);
	//s.cut();

	std::cout << "Paint Background start" << std::endl;
	func::paintBackground(vox, dim, dim, dim, 150);
	std::cout << "Paint Background end" << std::endl;

        std::cout << "Split/Merge start" << std::endl;
        std::vector<imgdata::Fracture> frac = func::splitMerge(vox, dim, dim, dim);
        std::cout << "Split/Merge end" << std::endl;
	

	std::cout << frac.size() << " fractures detected"<< std::endl;
	int sum(0);
	int cc(0);
	for(std::vector<Fracture>::iterator i = frac.begin(); i != frac.end(); ++i)
	{
		sum += i->getVoxels();
		if(cc%5 == 0)
		{
			i->setColour("white");
		}
		else if(cc%5 == 1)
		{
			i->setColour("red");
		}
		else if(cc%5 == 2)
		{
			i->setColour("green");
		}
		else if(cc%5 == 3)
		{
			i->setColour("blue");
		}
		else if( cc%5 == 4)
		{
			i->setColour("yellow");
		}
		cc++;
	}
	std::cout << sum << " fractured voxels detected" << std::endl;
	
	func::writeToPGM("big", frac, dim);

	//testing save
	func::saveGroupFractures(frac, "f123", dim);
	std::vector<Fracture> loaded = func::loadGroupFractures("f123");
	int loadedDim = func::loadDim("f123");

	unsigned char *** RBGformat = func::preparePPMCube(pgms, dim, loaded);
	func::writeCubeColour("fracsInColour", RBGformat, dim);*/



    }
    return 0;
}
