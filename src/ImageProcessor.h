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
	//recursively cuts parent into child splits until only comprised of
	//fractured voxels, then makes a fracture and collects it
	void split(imgpro::Split & parent, std::vector<imgdata::Fracture> & collector, int threshold, int & idCount);

	//tracing method
	void printCollection(std::vector<imgdata::Fracture> & coll);

	//convert dataset of unsigned chars to voxels
	imgdata::Voxel*** toVoxels(unsigned char *** & cube, int dim);

	//merges connecting fractures
	std::vector<imgdata::Fracture> merge(std::vector<imgdata::Fracture> & collection);

	//Encapsulates Split and Merge
	std::vector<imgdata::Fracture> splitMerge(imgdata::Voxel *** & imgArr3D, int rows, int cols, int depth);

	//paint background to an intensity (val)
	void paintBackground(imgdata::Voxel*** & cube, int rows, int cols, int depth, int val);
	
	//returns a portion of layer as a vector of voxels
	std::vector<imgdata::Voxel> getBlock(imgdata::Voxel ** & layer, int r, int c, int sizeX, int sizeY);

	//writes fractures onto blank (black) pgms in white
	void writeToPGM(const std::string & outFileName, std::vector<imgdata::Fracture> collection, int dim);

	//writes 3D structure(type: Voxel) to PGMS
	void writeCube(const std::string & outFileName, imgdata::Voxel *** sourceCube, int dim);

	//writes 3D structure to PPM (colour)
	void writeCubeColour(std::string name, unsigned char *** RBGformat, int dim);	

	//write 3D structure(type: unsigned chars) to PGMs 
	void writeRawCube(const std::string & outFileName, unsigned char *** sourceCube, int dim);

	//save fracture
	void saveFracture(imgdata::Fracture & fracture, std::string saveName);

	//save group of fractures
	void saveGroupFractures( std::vector<imgdata::Fracture> & fractures, char * folderName, int dim);
	
	//load fracture
	imgdata::Fracture loadFracture(std::string fileName);

	//load group of fractures
	std::vector<imgdata::Fracture> loadGroupFractures(std::string folderName);

	//load dimensions
	int loadDim(std::string folderName);

	//prepare cube for ppm format
	unsigned char *** preparePPMCube(int dim);

	//prepare cube for ppm with fractures
	unsigned char *** preparePPMCube(unsigned char *** & sourceCube, int dim, std::vector<imgdata::Fracture> & fractures);

	//transform orientation
	unsigned char *** transform(unsigned char *** & sourceCube, int dim, std::string axis);
	
}


#endif
