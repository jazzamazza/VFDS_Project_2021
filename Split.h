/* Noah De Nicola
 * 16/08/21
 * Split and Merge
 */

#ifndef SPLITMERGE_H
#define SPLITMERGE_H

#include <vector>
#include <memory>
#include <iostream>

#include "Voxel.h"

class Split
{
	private:
		imgdata::Voxel*** data;
		int depth, rows, cols;
		bool allFracture, someFracture; 
		std::vector< std::shared_ptr<Split> > children;
	public:
		//constructors
		Split();
		~Split();
		Split(imgdata::Voxel*** & data, int depth, int rows, int cols);
		//other 4
		Split(const Split & s);
		Split& operator=(const Split & s);
		Split(Split && s);
		Split& operator=(Split && s);
		
		void cut();
		void test();
		bool getAllFrac();
		bool getSomeFrac();
		imgdata::Voxel *** getData();
		int getDepth();
		int getRows();
		int getCols();
		std::vector<int> getDim();
		std::vector<std::shared_ptr<Split>> getKids();
		std::vector<imgdata::Voxel> getBoundary();
		friend std::ostream & operator<<(std::ostream & out, Split & s);
		

};


#endif
