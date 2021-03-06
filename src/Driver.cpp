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
#include "VolumeVisualizer.h"
#include "RaySampler.h"

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

	std::vector<Fracture> loaded = func::loadGroupFractures("f123");
	int loadedDim = func::loadDim("f123");

	unsigned char *** pgmCube = func::addFracturesToCube(pgms, loaded, loadedDim);
//	func::writeRawCube("fracsInColour", pgmCube, loadedDim);


	raycst::VolumeVisualizer vv(256);
    	int dim = ctr.getDim(files);

    	raycst::RaySampler rs(dim, 2);

	//write out
    	for (int i = 0; i < 18; ++i) 
	{
    		unsigned char ** ip = rs.sample(pgmCube, vv);
       	 	vv.moveCOP(0);
        	std::string sz = std::to_string(i);
        	std::ofstream out("out/castup"+sz+".pgm", std::ofstream::binary);
        	out << "P5" <<"\n";
       	 	out << dim << " ";
        	out << dim << "\n";
        	out << "255" << "\n";

        	char* wbuf = new char[dim];
        	for(int x=0; x<dim; x++)
        	{
        	    wbuf = reinterpret_cast<char *>(ip[x]);
        	    out.write(wbuf, dim);
        	}

        	out.close();
    	}


/*
	//std::vector<Fracture> blank({});
	//unsigned char *** RBGformat = func::preparePPMCube(pgms, dim, blank);
	//func::writeCubeColour("ogInColour",RBGformat, dim);



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
*/	
	//save
	//func::saveGroupFractures(frac, "f123", dim);

	//load


    }
    return 0;
}
