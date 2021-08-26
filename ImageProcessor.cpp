/* Noah De Nicola
 * 16/08/21
 * misc.cpp
 */

#include "Split.h"
#include "Voxel.h"
#include "ImageProcessorFunc.h"
#include "Fracture.h"

int main(void)
{
	using namespace imgdata;
	//construct Set
	int d = 5;
	int r = 5;
	int c = 5;

	Voxel*** cube = new Voxel**[d];
	for(int z = 0; z < d; z++)
	{
		Voxel** set = new Voxel*[r];
		for(int x = 0; x < r; x++)
		{
			Voxel * row = new Voxel[c];
			for(int y = 0; y < c; y++)
			{
				row[y] = Voxel(x,y,z,1);
			}
			set[x] = row;
		}
		cube[z] = set;
	}
	//make fracture
	for(int z = 0; z < 5; z++)
        {
                for(int x = 1; x < 3 ; x++)
                {
                        for(int y = 1; y < 3; y++)
                        {
                                cube[z][x][y] = Voxel(x,y,z,0);
                        }
                }
        }



	//Start Split and merge
	Split MotherSplit(cube, d, r, c);
	std::cout << MotherSplit << "\n" << std::endl;

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


	/*for(int l=0;l < MSDim[0]*MSDim[1]; l++)
	{
		std::cout << flatGrid[l] << " ";
		if((l+1)%MSDim[1] == 0)
		{
			std::cout << "" << std::endl;
		}
	}
*/
	for(int t =0; t < existingFractures.size(); t++)
	{
		std::cout << "\nFracture " << t << "\n" << existingFractures[t] << std::endl;
		
	}
	
	


	return 0;
}

