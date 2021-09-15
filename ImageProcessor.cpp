/* Noah De Nicola
 * 24/08/2021
 * func.cpp
 */

#include "ImageProcessor.h"

using namespace imgdata;

//global
int ID = 0;
int check(0);
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
        std::cout << "collected" << std::endl;
        func::printCollection(collection);


	//loop
	bool change(true);
	while(change)
	{
		change = false;
		std::vector<int> toErase;
	        //iterate through the collected fracture Objects. (fractured pixels)
	        for(int i = 0; i + 1 < collection.size(); i+=2)
	        {	
			if(collection[i].meets(collection[i+1]) )
			{
				change = true;
				collection[i].join(collection[i+1]);
				std::cout << "PB " << i +1 << std::endl;
				toErase.push_back(i+1);
			}
			else
			{
				if(collection[i] > collection[i+1])
				{
					Fracture temp = collection[i];
					collection[i] = collection[i+1];
					collection[i+1] = temp;
				}
			}
		}
		//func::printCollection(collection);
		std::cout << "erasing" << std::endl;
		for(int e = toErase.size()-1; e >= 0; e--)
		{
			std::cout << toErase[e] << std::endl;
			collection.erase(collection.begin() + toErase[e]);
		}
		//func::printCollection(collection);

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
					else
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
					jump = c; //revisit this line
                                        rblock = func::getBlock(layer, r, c, rowSize, colSize);
                                }

                                for(int i = 0; i < rblock.size(); i++)
                                {
                                        if(rblock[i].getIntensity() == 0)
                                        {
                                                cube[z][r + i/colSize][c + (i%colSize)] = Voxel(r + i/colSize, c + (i%colSize), z, 2);
                                        }
                                        else 
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
		//top side
		r = 0;
                c = 0;
                hit = false;
                while( c < cols)
                {
                        int colSize;
                        if(c + 3 < cols)
                        {
                                colSize = 3;
                        }
                        else
                        {
                                colSize = cols-c;
                        }

                        while( (!hit) && (r < rows) )
                        {
                                std::vector<Voxel> block;
                                int rowSize;
                                if(r+3 < rows)
                                {
                                        rowSize = 3;
                                        block = func::getBlock(layer, r, c, rowSize, colSize);
                                }
                                else
                                {
                                        rowSize = rows-r;
                                        block = func::getBlock(layer, r, c, rowSize, colSize);
                                }

                                for(int i = 0; i < block.size(); i++)
                                {
                                        if(block[i].getIntensity() == 0)
                                        {
                                                cube[z][r + i/colSize][c + (i%colSize)] = Voxel(r + i/colSize, c + (i%colSize), z, 2);
                                        }
                                        else
                                        {
						if(block[i].getIntensity() != 2)
						{
                                                	hit = true;
						}
                                        }
                                }
                                r += 3;
                        }
                        hit = false;
                        r = 0;
                        c += 3;
                }
		//bottom
		r = rows-3;
                c = 0;

                hit = false;
                while( c < cols)
                {
                        int colSize;
                        if(c + 3 < cols)
                        {
                                colSize = 3;
                        }
                        else
                        {
                                colSize = cols-c;
                        }
                        
                        while( (!hit) && (r >= 0) )
                        {
                                int rowSize;
                                std::vector<Voxel> rblock;
                                int jump;
                                if(r-3 >= 0)
                                {
                                        rowSize = 3;
                                        jump = 3;
                                        rblock = func::getBlock(layer, r, c, rowSize, colSize);
                                }
                                else
                                {
                                        rowSize = 3;
                                        jump = r; //revisit this line
					if(jump == 0)
					{
						jump++;	
					}
                                        rblock = func::getBlock(layer, r, c, rowSize, colSize);
                                }

                                for(int i = 0; i < rblock.size(); i++)
                                {
                                        if(rblock[i].getIntensity() == 0)
                                        {
                                                cube[z][r + i/colSize][c + (i%colSize)] = Voxel(r + i/colSize, c + (i%colSize), z, 2);
                                        }
                                        else
                                        {
						if(rblock[i].getIntensity() != 2)
						{
                                                	hit = true;
						}
                                        }
                                }
                                r -= jump;
                        }
                        hit = false;
                        r = rows-3;
                        c += 3;
                }
	
	}
	
}

