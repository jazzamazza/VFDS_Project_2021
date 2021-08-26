/* Noah De Nicola
 * 24/08/2021
 * func.h
 */

#ifndef FUNC_H
#define FUNC_H

#include "Split.h"
#include "Fracture.h"

namespace func
{
	void collect(Split & parent, std::vector<Split> & collector);
	void printCollection(std::vector<Split> & coll);
	void plotNeighbours(std::shared_ptr<int[]> & flatGrid, int index, int val, std::vector<int> dim);
	void addSplit(imgdata::Fracture & fracture, Split & split);
}


#endif
