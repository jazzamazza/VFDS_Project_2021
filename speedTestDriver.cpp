/*Noah De Nicola
 * 20 September 2021
 * test Speed Driver
*/

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>

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
	
	
	using namespace std::chrono;

	//CT
        std::cout << "CTReader start..." << std::endl;
	auto start = high_resolution_clock::now(); //start timing
        imgdata::Voxel*** vox = ctr.imgread::CTReader::readPGMStack(shape, dim);
	auto stop = high_resolution_clock::now();
        std::cout << "CTReader end..." << std::endl;
	auto x = duration_cast<milliseconds>(stop - start);
	float ctTime = x.count();
	std::cout << "Elapsed Time: " << ctTime/1000 << std::endl;

	//tracing
	//func::writeCube("originalCube", vox, dim); 

	//paint
	std::cout << "\nPaint Background start..." << std::endl;
	start = high_resolution_clock::now();
	func::paintBackground(vox, dim, dim, dim, 200);
	stop = high_resolution_clock::now();
	std::cout << "Paint Background end..." << std::endl;

	x = duration_cast<milliseconds>(stop - start);
       	float paintTime = x.count();
	std::cout << "Elapsed Time: " << paintTime/1000 << std::endl;	

	//tracing
	//func::writeCube("paintedCube", vox, dim);

        std::cout << "\nSplit/Merge start..." << std::endl;
	start = high_resolution_clock::now();
        std::vector<imgdata::Fracture> frac = func::splitMerge(vox, dim, dim, dim);
	stop = high_resolution_clock::now();
        std::cout << "Split/Merge end..." << std::endl;

	x = duration_cast<milliseconds>(stop - start);
	float splMrgTime = x.count();

	std::cout << "Elapsed Time: " << splMrgTime/1000 << std::endl;

	std::cout << "\nTotal Elapsed Time: " << (ctTime+paintTime+splMrgTime)/1000 << std::endl;


	/*for(std::vector<imgdata::Fracture>::iterator i = frac.begin(); i != frac.end(); ++i)
	{
		std::cout << *i << std::endl;
	}*/

	func::writeToPGM("fracturesInWhite", frac, dim);

        //std::cout << "delete pgm stack" << std::endl;
        //ctr.imgread::CTReader::deletePGMStack(vox, 128);   
    }
    
    return 0;
}
