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
	void collect(Split & parent, std::vector<imgdata::Fracture> & collector, int threshold);
	void printCollection(std::vector<imgdata::Fracture> & coll);
	void plotNeighbours(std::shared_ptr<int[]> & flatGrid, int index, int val, std::vector<int> dim);
	void addSplit(imgdata::Fracture & fracture, Split & split);
	std::vector<imgdata::Fracture> splitMerge(imgdata::Voxel*** & imgArr3D, int rows, int cols, int depth);
	void paintBackground(imgdata::Voxel*** & cube, int rows, int cols, int depth, int val);
	std::vector<imgdata::Voxel> getBlock(imgdata::Voxel ** & layer, int r, int c, int sizeX, int sizeY);
	void writeToPGM(const std::string & outFileName, std::vector<imgdata::Fracture> collection, int dim);
	void writeCube(const std::string & outFileName, imgdata::Voxel *** sourceCube, int dim);
}


#endif
