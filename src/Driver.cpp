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
	/*int dim = 256;
	unsigned char *** cube = new unsigned char ** [dim];
        for(int z = 0; z < dim; z++)
        {
                //prepare output
                unsigned char ** layer = new unsigned char * [dim*dim];
                for(int x = 0; x < dim*dim; x++)
                {
                        unsigned char * row = new unsigned char[3];
			if(false)//x%dim > 66*(z))
			{
				row[0] = 0;
				row[1] = 255;
				row[2] = 0;
				layer[x] = row;
			}
			else if(false)//x&dim > 33*(z))
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
				row[2] = int(255*float(z)/float(dim));
				layer[x] = row;
			}
                }
                cube[z] = layer;
        }

	func::writeCubeColour("noah", cube, dim);

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
		i->setColour("red");
		if(i->getVoxels() > 50)
		{
			//std::cout << *i << std::endl;
			toPrint.push_back(*i);
		}
	}

	std::cout << frac.size() << " fractures found"<< std::endl;


	//testing save
	func::saveGroupFractures(frac, "f123", dim);*/
	std::vector<Fracture> loaded = func::loadGroupFractures("f123");
	int loadedDim = func::loadDim("f123");
	int cc(0);
	for(std::vector<imgdata::Fracture>::iterator i = loaded.begin(); i != loaded.end(); ++i)
	{
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
		else if(cc&5 == 3)
		{
			i->setColour("blue");
		}
		else if( cc%5 == 4)
		{
			i->setColour("yellow");
		}
		cc++;
	}

	unsigned char *** RBGformat = func::preparePPMCube(loadedDim, loaded);
	func::writeCubeColour("fracsInColour", RBGformat, loadedDim);
		


	//func::writeToPGM("fracturesInWhite", frac, dim);
	//func::writeToPGM("savedANDloaded", loaded, dim);


    }
    return 0;
}
