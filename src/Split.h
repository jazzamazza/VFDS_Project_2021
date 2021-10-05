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
	class Split
	{
		private:
			imgdata::Voxel*** data;
			int depth, rows, cols;
			bool allFracture, someFracture; 
			std::vector< std::shared_ptr<Split> > children;
			int ID;
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
			std::vector<std::shared_ptr<Split>> getKids();
			std::vector<imgdata::Voxel> getBoundary();

			//operators
			friend std::ostream & operator<<(std::ostream & out, Split & s);
			bool operator!=(Split & s);

	};
}


#endif
