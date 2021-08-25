/* Noah De Nicola
 * 16/08/21
 * misc.cpp
 */

#include "Split.h"
#include "Voxel.h"
#include "ImageProcessorFunc.h"

int main(void)
{
	using namespace imgdata;
	//construct Set
	int d = 11;
	int r = 11;
	int c = 11;

	Voxel*** cube = new Voxel**[d];
	for(int z = 0; z < d; z++)
	{
		Voxel** set = new Voxel*[r];
		for(int x = 0; x < r; x++)
		{
			Voxel * row = new Voxel[c];
			for(int y = 0; y < c; y++)
			{
				row[y] = Voxel(z,x,y,1);
			}
			set[x] = row;
		}
		cube[z] = set;
	}
	//make fracture
	for(int z = 3; z < 7; z++)
        {
                for(int x = 3; x < 7; x++)
                {
                        for(int y = 3; y < 7; y++)
                        {
                                cube[z][x][y] = Voxel(z,x,y,0);
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
	std::cout << "collected" << std::endl;
	func::printCollection(collection);
	
	
	/*	
	std::vector<int> MSDim = MotherSplit.getDim();
	std::shared_ptr<int[]> flatGrid(new int[MSDim[0]*MSDim[1]]); // {rows, cols}
	
	//fracture class for now////////////////
	std::vector< std::vector<Split> > fractures;
	std::vector< std::vector<int> > fracIDs;
	/////////////////////////////////////
	
	
	//group into fractures
	int count = 0;
	//iterate through the collected Split Objects. Each Split object is only made up of 0s(fractured pixels)
	for(std::vector<Split>::iterator i = collection.begin(); i != collection.end(); ++i)
	{
		count++;//incremenet to 1

		//only use the boundary pixels of the split
		std::vector<Pixel> boundary = i->getBoundary();	

		//this split has not been pushed back yet
		bool pushedBack = false;

		//iterate through the boundary pixels
		for(std::vector<Pixel>::iterator b = boundary.begin(); b != boundary.end(); ++b)
		{

			//get 1D index from 2D location
			int index = (MSDim[1]*b->getX())+b->getY();
			
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
								fractures[f].push_back(*i);
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
			std::vector<Split> newFracture;
			newFracture.push_back(*i);
			fractures.push_back(newFracture);
			//add to FracIDs
			std::vector<int> newFracIDs;
			newFracIDs.push_back(count);
			fracIDs.push_back(newFracIDs);
		}
	}


	for(int l=0;l < MSDim[0]*MSDim[1]; l++)
	{
		std::cout << flatGrid[l] << " ";
		if((l+1)%MSDim[1] == 0)
		{
			std::cout << "" << std::endl;
		}
	}

	for(int t =0; t < fractures.size();t++)
	{
		std::cout << "\nFracture " << t << std::endl;
		func::printCollection(fractures[t]);
		
	}
*/
	
	


	return 0;
}

