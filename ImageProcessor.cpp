/* Noah De Nicola
 * 24/08/2021
 * func.cpp
 */

#include "ImageProcessor.h"

using namespace imgdata;

//global
int ID = 0;

void func::collect(Split & parent, std::vector<Fracture> & collector)
{
        if(parent.getAllFrac()) //if all 0's
        {
		//std::cout << "all\n" << parent << std::endl;
		Fracture f(ID++, "black");
		f.insertSplit(parent);
                collector.push_back(f);

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

void func::printCollection(std::vector<Fracture> & coll)
{
	for(std::vector<Fracture>::iterator i = coll.begin(); i != coll.end(); ++i)
	{
		std::cout << *i << std::endl;
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
        //std::cout << MotherSplit << "\n" << std::endl;    //uncomment for case demo

        //initiate collection
        std::vector<Fracture> collection;

        //test before collect
        MotherSplit.test();

        //collect 
        func::collect(MotherSplit, collection);

        //print
        //std::cout << "collected" << std::endl;
        //func::printCollection(collection);


	//loop
	bool change(true);
	while(change)
	{
		change = false;
		std::vector<int> usedIDs;
		std::vector<int> toErase;

		//group into fractures   
        	int count(0);
	
	        //iterate through the collected fracture Objects. (fractured pixels)
	        for(std::vector<Fracture>::iterator i = collection.begin(); i != collection.end(); ++i)
	        {
			Fracture f1(*i);
		
			//check if this split has been used
			bool used(false);
			for(std::vector<int>::iterator u = usedIDs.begin(); u != usedIDs.end(); ++u)
			{
				if(*u == f1.getID())
				{
					used = true;
				}
			}
			if(!used)
			{
               			std::vector<Voxel> f1Coords = f1.getCoords();
				for(std::vector<Fracture>::iterator p = collection.begin(); p != collection.end(); ++p)
				{
					Fracture f2(*p);
					
					bool used2(false);
					for(std::vector<int>::iterator u = usedIDs.begin(); u != usedIDs.end(); ++u)
					{
						if(*u == f2.getID())
						{
							used2 = true;
						}	
					}
					if(!used2)
					{
						bool inserted(false);
	
						//only use boundary
						std::vector<Voxel> f2Coords = f2.getCoords();
			
						if(f1.getID() != f2.getID()) //doesnt check against itself
						{
       		 		        		//iterate through the boundary pixels of main split
       		        				for(std::vector<Voxel>::iterator v1 = f1Coords.begin(); v1 != f1Coords.end(); ++v1)
        	        				{
								if(inserted)
								{
									//only needs 1 match
									break;
								}
								else
								{
									for(std::vector<Voxel>::iterator v2 = f2Coords.begin(); v2 != f2Coords.end(); ++v2)
									{
										if(func::touching(*v1,*v2))
										{
											i->join(*p);
											change = true;
											usedIDs.push_back(f2.getID());
											toErase.push_back(f2.getID());
											inserted = true;
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		for(std::vector<int>::iterator i = toErase.begin(); i != toErase.end(); ++i)
		{
			for(std::vector<Fracture>::iterator p = collection.begin(); p != collection.end(); ++p)
			{
				if(p->getID() == *i)
				{
					collection.erase(p);
					break;
				}
			}
		}

	}
	return collection;


}

std::vector<Voxel> func::getBlock(Voxel ** & layer, int r, int c, int sizeX, int sizeY)
{
	std::vector<Voxel> ret;
	for(int x = r; x < r+sizeX; x++)
	{
		for(int y = c; y < c+sizeY; y++)
		{
			ret.push_back(layer[x][y]);
		}
	}
	return ret;
}

void func::paintBackground(Voxel*** & cube, int rows, int cols, int depth)
{
	for(int z = 0; z < depth; z++)
	{

		Voxel ** layer = cube[z];	

		//left side (left to right)
		
		int r(0);
		int c(0);

		bool hit(false);
		while( r < rows)
		{
			int rowSize;
			if(r + 3 < rows)
			{
				rowSize = 3;
			}
			else
			{
				rowSize = rows-r;
			}

			while( (!hit) && (c < cols) )
			{
				std::vector<Voxel> block;
				int colSize;
				if(c+3 < cols)
				{
					colSize = 3;
					block = func::getBlock(layer, r, c, rowSize, colSize);
				}
				else
				{
					colSize = cols-c;
					block = func::getBlock(layer, r, c, rowSize, colSize);
				}

				for(int i = 0; i < block.size(); i++)
				{
					if(block[i].getIntensity() == 0)
					{
						cube[z][r + i/colSize][c + (i%colSize)] = Voxel(r + i/colSize, c + (i%colSize), z, 2);
					}
					else if(block[i].getIntensity() != 0)
					{
						hit = true;
					}
				}
				c += 3;
			}
			hit = false;
			c = 0;
			r += 3;
		}
		//rightside
		
		r = 0;
               	c = cols-3;

                hit = false;
                while( r < rows)
                {
                        int rowSize;
                        if(r + 3 < rows)
                        {
                                rowSize = 3;
                        }
                        else
                        {
                                rowSize = rows-r;
                        }
			
                        while( (!hit) && (c >= 0) )
                        {
                                int colSize;
				std::vector<Voxel> rblock;
				int jump;
                                if(c-3 >= 0)
                                {
                                        colSize = 3;
					jump = 3;
                                        rblock = func::getBlock(layer, r, c, rowSize, colSize);
                                }
                                else
                                {
                                        colSize = 3;
					jump = c;
                                        rblock = func::getBlock(layer, r, c, rowSize, colSize);
                                }

                                for(int i = 0; i < rblock.size(); i++)
                                {
                                        if(rblock[i].getIntensity() == 0)
                                        {
                                                cube[z][r + i/colSize][c + (i%colSize)] = Voxel(r + i/colSize, c + (i%colSize), z, 2);
                                        }
                                        else if(rblock[i].getIntensity() != 0)
                                        {
                                                hit = true;
                                        }
                                }
                                c -= jump;
                        }
                        hit = false;
                        c = cols-3;
                        r += 3;
                }

		

	}
	
}

//global
std::vector<Voxel> directions = {Voxel(1,0,0,0), Voxel(-1,0,0,0), Voxel(0,1,0,0), Voxel(0,-1,0,0), Voxel(0,0,1,0), Voxel(0,0,-1,0)};

bool func::touching(const Voxel & a, const Voxel & b) //change to split memeber function
{
	std::vector<Voxel> aNeighbours;
	bool ret = false;
	for(std::vector<Voxel>::iterator i = directions.begin(); i != directions.end(); i++)
	{
		aNeighbours.push_back(*i+a);
	}
	for(std::vector<Voxel>::iterator i = aNeighbours.begin(); i != aNeighbours.end(); ++i)
	{
		Voxel v(*i);
		if(b == v)
		{
			ret = true;
		}
	}
	return ret;	
}
