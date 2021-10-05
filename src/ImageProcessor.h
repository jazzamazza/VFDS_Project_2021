/* Noah De Nicola
 * 24/08/2021
 * func.h
 */

#ifndef FUNC_H
#define FUNC_H

#include "Split.h"
#include "Fracture.h"
#include "Voxel.h"
#include <set>

namespace func
{
	//collects all fractured voxels
	void collect(imgpro::Split & parent, std::vector<imgdata::Fracture> & collector, int threshold);
	//tracing method
	void printCollection(std::vector<imgdata::Fracture> & coll);
	//Split & Merge
	std::vector<imgdata::Fracture> splitMerge(imgdata::Voxel*** & imgArr3D, int rows, int cols, int depth);

	//paint background to intensity (val)
	void paintBackground(imgdata::Voxel*** & cube, int rows, int cols, int depth, int val);
	
	//returns a portion of layer as a vector of voxels
	std::vector<imgdata::Voxel> getBlock(imgdata::Voxel ** & layer, int r, int c, int sizeX, int sizeY);

	//writes fractures to pgms
	void writeToPGM(const std::string & outFileName, std::vector<imgdata::Fracture> collection, int dim);

	//writes whole cube(CT scan space) to pgms
	void writeCube(const std::string & outFileName, imgdata::Voxel *** sourceCube, int dim);

	//writes colour  cube
	void writeCubeColour(std::string name, unsigned char *** RBGformat, int dim);	

	//Write raw unsigned chars
	void writeRawCube(const std::string & outFileName, unsigned char *** sourceCube, int dim);

	//save fracture
	void saveFracture(imgdata::Fracture & fracture, std::string saveName);

	//save group of fractures
	void saveGroupFractures( std::vector<imgdata::Fracture> & fractures, char * folderName, int dim);
	
	//load fracture
	imgdata::Fracture loadFracture(std::string fileName);

	//load group of fractures
	std::vector<imgdata::Fracture> loadGroupFractures(std::string folderName);

	//load dim
	int loadDim(std::string folderName);

	//prepare cube for ppm format
	unsigned char *** preparePPMCube(int dim);

	//prepare cube with fractures
	unsigned char *** preparePPMCube(int dim, std::vector<imgdata::Fracture> & fractures);
}


#endif
