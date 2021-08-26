/* Noah De Nicola
 * 24/08/2021
 * func.cpp
 */

#include "ImageProcessor.h"
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
	
	//left and right
	if(index%dim[1] == 0)
	{
		actions[0] = 0;	
	}
	if(index%dim[1] == dim[1]-1)
	{
		actions[1] = 0;
	}

	//forward and back
	int layer = index / (dim[0]*dim[1]);
	int tempIndex = index - dim[0]*dim[1]*layer;
	if(tempIndex/dim[1]==0)
	{
		actions[2] = 0;
	}
	if(tempIndex/dim[1] == dim[0]-1)
	{
		actions[3] = 0;
	}
	if(index/ (dim[1]*dim[0]) == 0)
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

std::vector<Fracture> func::splitMerge(Voxel*** & imgArr3D, int rows, int cols, int depth)
{
	//Start Split and merge
        Split MotherSplit(imgArr3D, depth, rows, cols);
        //std::cout << MotherSplit << "\n" << std::endl;

        //initiate collection
        std::vector<Split> collection;

        //test before collect
        MotherSplit.test();

        //collect 
        func::collect(MotherSplit, collection);

        //print
        //std::cout << "collected" << std::endl;
        //func::printCollection(collection);


        std::vector<int> MSDim = MotherSplit.getDim();
        std::shared_ptr<int[]> flatGrid(new int[MSDim[0]*MSDim[1]*MSDim[2]]); // {rows, cols,depth}

        //fracture class for now
        std::vector<Fracture> existingFractures;
        std::vector< std::vector<int> > fracIDs;

	//group into fractures
        int count = 0;
        int IDcount = 0;
        //iterate through the collected Split Objects. Each Split object is only made up of 0s(fractured pixels)
        for(std::vector<Split>::iterator i = collection.begin(); i != collection.end(); ++i)
        {
                count++;//incremenet to 1

                //only use the boundary pixels of the split
                std::vector<Voxel> boundary = i->getBoundary();

                //this split has not been pushed back yet
                bool pushedBack = false;

                //iterate through the boundary pixels
                for(std::vector<Voxel>::iterator b = boundary.begin(); b != boundary.end(); ++b)
                {
                        //get 1D index from 3D location
                        int index = (MSDim[1]*b->getX()) + b->getY() + b->getZ()*(MSDim[0]*MSDim[1]);

                        /*std::cout << "Flat Grid " <<  index <<std::endl;
                        for(int p = 0; p < MSDim[0]*MSDim[1]*MSDim[2]; p++)
                        {
                                std::cout << flatGrid[p] << " ";
                                if((p+1)%(MSDim[1])==0)
                                {
                                        std::cout << "" << std::endl;
                                }
                                if((p+1)%(MSDim[1]*MSDim[0])==0)
                                {
                                        std::cout << "\n" << std::endl;
                                }
                        }
                        std::cout << "\n";*/



                        //plot point in if nothing is present already
                        if(flatGrid[index] == 0)
                        {
                                flatGrid[index] = count;
                        }
                        //if something is present - add to present fracture and add count to present fracture ID(diff count values) list(unless already happened)
                        else if(flatGrid[index] != 0)
                        {
                                for(int f=0; f<fracIDs.size();f++)
                                {
                                        for(int ID=0; ID < fracIDs[f].size(); ID++)
                                        {
                                                if(flatGrid[index] == fracIDs[f][ID])
                                                {
                                                        if(!pushedBack)
                                                        {
                                                                fracIDs[f].push_back(count);
                                                                func::addSplit(existingFractures[f], *i); //implement
                                                                pushedBack = true;
                                                        }
                                                }
                                        }
                                }
                        }
                        //plot neighbours
                        func::plotNeighbours(flatGrid, index, count, MSDim);

                }
                //if not pushed back then this is split is apart of a new fracture
                if(!pushedBack)
                {
                        //make new fracture
                        Fracture newFracture(IDcount++, "blank");

                        func::addSplit(newFracture, *i);

                        existingFractures.push_back(newFracture);

                        //add to FracIDs
                        std::vector<int> newFracIDs;
                        newFracIDs.push_back(count);
                        fracIDs.push_back(newFracIDs);
                }
        }

	//print fractures
        for(int t =0; t < existingFractures.size(); t++)
        {
                std::cout << existingFractures[t] << std::endl;

        }

	return existingFractures;

}
