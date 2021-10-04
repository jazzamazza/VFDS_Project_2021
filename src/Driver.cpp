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
        std::cout << "Please provide path to header as an argument" << std::endl;
        return 1;
    }
    else
    {
        files = argv[1];
        std::cout<<files<<"\n";
        //shape = findShape(files);
        //dim = findDim(files);

        std::cout << "CTReader start" << std::endl;
        //imgdata::Voxel*** vox = ctr.imgread::CTReader::readPGMStack(files);
        unsigned char*** pgms = ctr.imgread::CTReader::readPGMStack(files);
        //std::cout << "first voxel" << pgms[0];
        std::cout << "CTReader end" << std::endl;
    }
/*
	func::writeCube("originalCube", vox, dim); 

	std::cout << "Paint Background start" << std::endl;
	func::paintBackground(vox, dim, dim, dim, 200);
	std::cout << "Paint Background end" << std::endl;

	func::writeCube("paintedCube", vox, dim);


        std::cout << "Split/Merge start" << std::endl;
        std::vector<imgdata::Fracture> frac = func::splitMerge(vox, dim, dim, dim);
        std::cout << "Split/Merge end" << std::endl;

	for(std::vector<imgdata::Fracture>::iterator i = frac.begin(); i != frac.end(); ++i)
	{
		std::cout << *i << std::endl;
	}

	//testing save
	func::saveGroupFractures(frac, "fractures");

	func::writeToPGM("fracturesInWhite", frac, dim);

        //std::cout << "delete pgm stack" << std::endl;
        //ctr.imgread::CTReader::deletePGMStack(vox, 128);   
    }
    */
    return 0;
}
