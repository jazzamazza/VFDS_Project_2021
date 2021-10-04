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
	int dim = 100;
	unsigned char *** cube = new unsigned char ** [dim];
        for(int z = 0; z < dim; z++)
        {
                //prepare output
                unsigned char ** layer = new unsigned char * [dim*dim];
                for(int x = 0; x < dim*dim; x++)
                {
                        unsigned char * row = new unsigned char[3];
			if(x%dim > 66)
			{
				row[0] = 0;
				row[1] = 255;
				row[2] = 0;
				layer[x] = row;
			}
			else if(x&dim > 33)
			{
				row[0] = 255;
				row[1] = 0;
				row[2] = 0;
				layer[x] = row;
			}
			else
			{
                        	row[0] = 0;
				row[1] = 0;
				row[2] = 255;
				layer[x] = row;
			}
                }
                cube[z] = layer;
        }

	func::writeCubeColour("noah", cube, dim);

/*
        std::cout << "CTReader start" << std::endl;
        unsigned char*** pgms = ctr.imgread::CTReader::readPGMStack(files);
        std::cout << "CTReader end" << std::endl;
    
    	int dim = ctr.getDim(files);
	imgfltr::BilateralFilter<unsigned char> bf(dim, 4, 0.005);
	std::cout << "Filter Conversion start" << std::endl;
	Voxel *** vox = bf.toVoxel(pgms);
	std::cout << "Filter Conversion end" << std::endl;
	


	std::cout << "Paint Background start" << std::endl;
	func::paintBackground(vox, dim, dim, dim, 150);
	std::cout << "Paint Background end" << std::endl;

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

	std::cout << toPrint.size() << " fractures found"<< std::endl;

	//testing save
	func::saveGroupFractures(toPrint, "fractures");
	//std::vector<Fracture> loaded = func::loadGroupFractures("fractures");

	func::writeToPGM("fracturesInWhite", toPrint, dim);
	//func::writeToPGM("savedANDloaded", loaded, dim);
*/


    }
    return 0;
}
