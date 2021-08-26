/* Noah De Nicola
 * 24/08/2021
 * func.cpp
 */

#include "ImageProcessorFunc.h"
using namespace imgdata;
void func::collect(Split & parent, std::vector<Split> & collector)
{
        if(parent.getAllFrac()) //if all 0's
        {
		//std::cout << "all\n" << parent << std::endl;
                collector.push_back(parent);

        }
        else
        {
                parent.cut();
                std::vector<std::shared_ptr<Split>> vec = parent.getKids();
                for(std::vector<std::shared_ptr<Split>>::iterator i = vec.begin(); i != vec.end(); ++i)
                {
                        std::shared_ptr<Split> kid = *i;
			kid->test();
                        if(kid->getSomeFrac()) //if any 0's
                        {
				//std::cout << "some\n" << *kid << std::endl;
                                collect(*kid, collector);
                        }
                }
        }
}

void func::printCollection(std::vector<Split> & coll)
{
	for(std::vector<Split>::iterator i = coll.begin(); i != coll.end(); ++i)
        {
                Voxel*** temp = i->getData();
		std::vector<int> dims = i->getDim();
		for(int z = 0; z < dims[2]; z++)
		{
                	for(int x = 0; x < dims[0]; x++)
			{
				for(int y = 0; y < dims[1]; y++)
				{
					std::cout << "(" << temp[z][x][y].getZ() << ","<< temp[z][x][y].getX() << "," << temp[z][x][y].getY() << ")";
				}
				std::cout << "" << std::endl;
			}
			std::cout << "\n";	
		}
        }

}


void func::plotNeighbours(std::shared_ptr<int[]> & flatGrid, int index, int val, std::vector<int> dim)
{
	std::vector<int> actions = {-1, 1, -dim[1], dim[1], -dim[1]*dim[0], dim[1]*dim[0]};
	if(index%dim[1] == 0)
	{
		actions[0] = 0;	
	}
	if(index%dim[1] == dim[1]-1)
	{
		actions[1] = 0;
	}
	if(index/dim[1]==0)
	{
		actions[2] = 0;
	}
	if(index/dim[1] == dim[0]-1)
	{
		actions[3] = 0;
	}
	if(index/(dim[1]*dim[0]) == 0)
	{
		actions[4] = 0;
	}
	if(index/(dim[1]*dim[0]) == dim[2]-1)
	{
		actions[5] = 0;
	}
	for(std::vector<int>::iterator a = actions.begin(); a != actions.end(); ++a)
	{
		int nIndex = index + *a;
		flatGrid[nIndex] = val;

	}
}

void func::addSplit(Fracture & fracture, Split & split)
{
	Voxel *** dataSet = split.getData();
	std::vector<int> d = split.getDim();
	for(int z = 0; z < d[2]; z++)
	{
		for(int x = 0; x < d[0]; x++)
		{
			for(int y = 0; y < d[1]; y++)
			{
				fracture.insertVoxel(dataSet[z][x][y]);
			}
		}	
	}
}
