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
namespace imgpro
{
	//represents a portion of a 3D data set
	class Split
	{
		private:
			imgdata::Voxel*** data; //data
			int depth, rows, cols; //dimensions
			bool allFracture, someFracture; //whether the region is only fractured voxels or some fractured voxels
			Split * children; // Each split object has 8 sub splits(the region split into 8)
			int ID; //ID
		public:
			//core 3
			Split();
			~Split();
			Split(imgdata::Voxel*** & data, int depth, int rows, int cols);

			//big  4
			Split(const Split & s);
			Split& operator=(const Split & s);
			Split(Split && s);
			Split& operator=(Split && s);
			
			//void
			void cut();
			void test(int threshold);

			//set
			void setID(int ID);

			//get
			bool getAllFrac();
			bool getSomeFrac();
			imgdata::Voxel *** getData();
			int getDepth();
			int getRows();
			int getCols();
			int getID();
			std::vector<int> getDim();
			Split * getKids();
			std::vector<imgdata::Voxel> getBoundary();

			//operators
			friend std::ostream & operator<<(std::ostream & out, Split & s);
			bool operator!=(Split & s);

	};
}


#endif
