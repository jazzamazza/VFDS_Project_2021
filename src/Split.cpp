/* Noah De Nicola
 * 16/08/21
 * Split.cpp
 */

#include "Split.h"
using namespace imgdata;
//Default
imgpro::Split::Split(): data(nullptr), children(nullptr), allFracture(false), someFracture(true), depth(0), rows(0), cols(0), ID(-1){}

//Destructor
imgpro::Split::~Split()
{
	if(this->children != nullptr)
	{
		delete [] children;
	}
}

//Custom
imgpro::Split::Split(Voxel*** & data, int depth, int rows, int cols): data(data), children(nullptr), allFracture(false), someFracture(true), depth(depth), rows(rows), cols(cols), ID(-1){}

//Copy Constructor
imgpro::Split::Split(const Split & s): data(nullptr), children(nullptr), allFracture(s.allFracture), someFracture(s.someFracture), depth(s.depth), rows(s.rows), cols(s.cols), ID(s.ID)
{
	if(s.data != nullptr)
	{
		Voxel*** cube = new Voxel** [this->depth];
		for(int z = 0; z < this->depth; z++)
		{
			Voxel** grid = new Voxel* [this->rows];
                	for(int x = 0; x < this->rows; x++)
                	{
                		Voxel* row = new Voxel[this->cols];
                        	for(int y = 0; y < this->cols; y++)
                        	{
                        		row[y] = s.data[z][x][y];
                        	}
                        	grid[x] = row;
                	}
			cube[z] = grid;
		}
                this->data = std::move(cube);
	}
	imgpro::Split * temp = new imgpro::Split[8];
	if(s.children != nullptr)
	{
		for(int i = 0; i < 8; i++)
		{
			temp[i] = s.children[i];
		}
	}
	this->children = std::move(temp);
}

//Copy Assignment Operator
imgpro::Split& imgpro::Split::operator=(const imgpro::Split & s)
{
	if(this != &s)
	{
		if(this->data != nullptr)
		{
                	for(int z = 0; z < this->depth; z++)
                	{
                       		for(int x = 0; x < this->rows; x++)
                       		{
                               		delete [] this->data[z][x];
                       		}
                       		delete [] this->data[z];
                	}
                	delete [] this->data;
        	}
		if(this->children != nullptr)
		{
			delete [] children;
		}

		this->allFracture = s.allFracture;
		this->someFracture = s.someFracture;
		this->depth = s.depth;
		this->rows = s.rows;
		this->cols = s.cols;
		this->ID = s.ID;
		
		imgpro::Split * temp = new imgpro::Split [8];		
		if(s.children != nullptr)
		{
			for(int i = 0; i < 8; i++)
			{
				temp[i] = s.children[i];
			}
		}
		this->children = std::move(temp);
		
		if(s.data != nullptr)
		{
			Voxel*** cube = new Voxel** [this->depth];
                	for(int z = 0; z < this->depth; z++)
                	{
                        	Voxel** grid = new Voxel* [this->rows];
                        	for(int x = 0; x < this->rows; x++)
                        	{
                                	Voxel* row = new Voxel[this->cols];
                                	for(int y = 0; y < this->cols; y++)
                                	{
                                	        row[y] = s.data[z][x][y];
                                	}
                                	grid[x] = row;
                        	}	
                        	cube[z] = grid;
                	}
                	this->data = std::move(cube);
		}
	}
	return *this;
}

//Move Constructor 
imgpro::Split::Split(imgpro::Split && s): data(nullptr), children(nullptr), allFracture(s.allFracture), someFracture(s.someFracture), depth(s.depth), rows(s.rows), cols(s.cols), ID(s.ID)
{

	if(s.data != nullptr)
	{
		this->data = std::move(s.data);
	}
	if(s.children != nullptr)
	{
		this->children = std::move(s.children);
	}
	
}

//Move Assignment Operator
imgpro::Split& imgpro::Split::operator=(imgpro::Split && s)
{
	if (this != &s)
	{
		if(this->data != nullptr)
		{
			for(int z = 0; z < this->depth; z++)
                        {
                                for(int x = 0; x < this->rows; x++)
                                {
                                        delete [] this->data[z][x];
                                }
                                delete [] this->data[z];
                        }
                        delete [] this->data;
		}
		if(this->children != nullptr)
		{
			delete [] this->children;
		}

		if(s.data != nullptr)
		{
			this->data = std::move(s.data);
		}
		if(s.children != nullptr)
		{
			this->children = std::move(s.children);
		}
		this->allFracture = s.allFracture;
		this->someFracture = s.someFracture;
		this->depth = s.depth;
                this->rows = s.rows;
                this->cols = s.cols;
		this->ID = s.ID;


	}
	return *this;
}

//returns array of kids
imgpro::Split* imgpro::Split::getKids()
{
	return this->children;
}

//returns dimensions of split as a vector of ints
std::vector<int> imgpro::Split::getDim()
{
	std::vector<int> ret({this->rows, this->cols, this->depth});
	return ret;
}

//returns deptp
int imgpro::Split::getDepth()
{
	return this->depth;
}

//returns length
int imgpro::Split::getRows()
{
	return this->rows;
}

//returns breadth
int imgpro::Split::getCols()
{
	return this->cols;
}

//returns id
int imgpro::Split::getID()
{
	return this->ID;
}

//returns the data
Voxel*** imgpro::Split::getData()
{
	return this->data;
}

//tests the dataset to update AllFractures and someFractures
void imgpro::Split::test(int threshold)
{
	this->someFracture = false;
	this->allFracture = true;
	for(int z=0; z<this->depth; z++)
	{
		for(int x=0; x < this->rows; x++)
		{
			for(int y = 0; y < this->cols; y++)
			{
				if (this->data[z][x][y].getIntensity() < threshold)
				{
					this->someFracture = true;
				}
				if (this->data[z][x][y].getIntensity() > threshold)
				{
					this->allFracture = false;
				}			
			}
		}
	}	
}

//returns true if all Voxels are fractured, else false
bool imgpro::Split::getAllFrac()
{
	return this->allFracture;
}

//returns true if some Voxels are fractured, else false
bool imgpro::Split::getSomeFrac()
{
	return this->someFracture;
}

//splits dataset into 8 regions, assigns each regions to a child split 
void imgpro::Split::cut()
{
	this->children = new Split[8];
	//get cut spot
	int cuty = cols/2;
	int cutx = rows/2;
	int cutz = depth/2;
		
	//8 Regions
		
	//1 TBL - Top Back Left
	Voxel*** TBLcube = new Voxel**[cutz];
	for(int z = 0; z < cutz; z++)
	{
		Voxel** grid = new Voxel*[cutx];
		for(int x = 0; x < cutx; x++)
		{
			Voxel* row = new Voxel[cuty];
			for(int y = 0; y < cuty; y++)
			{
				row[y] = std::move(this->data[z][x][y]);	
			}
			grid[x] = row;
		}
		TBLcube[z] = grid;
	}
	this->children[0] = Split(TBLcube, cutz, cutx, cuty);

	//2 TBR - Top Back Right
	Voxel*** TBRcube = new Voxel**[cutz];
        for(int z = 0; z < cutz; z++)
        {
                Voxel** grid = new Voxel*[cutx];
                for(int x = 0; x < cutx; x++)
                {
                        Voxel* row = new Voxel[cols-cuty];
                        for(int y = cuty; y < cols; y++)
                        {
                                row[y-cuty] = std::move(this->data[z][x][y]);
                        }
                        grid[x] = row;
                }
                TBRcube[z] = grid;
        }
        this->children[1] = Split(TBRcube, cutz, cutx, cols-cuty); 
	
	//3 TFL - Top Front Left
	Voxel*** TFLcube = new Voxel**[cutz];
        for(int z = 0; z < cutz; z++)
        {
                Voxel** grid = new Voxel*[rows-cutx];
                for(int x = cutx; x < rows; x++)
                {
                        Voxel* row = new Voxel[cuty];
                        for(int y = 0; y < cuty; y++)
                        {
                                row[y] = std::move(this->data[z][x][y]);
                        }
                        grid[x-cutx] = row;
                }
                TFLcube[z] = grid;
        }
        this->children[2] = Split(TFLcube, cutz, rows-cutx, cuty);
	
	//4 TFR - Top Front Right
	Voxel*** TFRcube = new Voxel**[cutz];
        for(int z = 0; z < cutz; z++)
        {
                Voxel** grid = new Voxel*[rows-cutx];
                for(int x = cutx; x < rows; x++)
                {
                        Voxel* row = new Voxel[cols-cuty];
                        for(int y = cuty; y < cols; y++)
                        {
                                row[y-cuty] = std::move(this->data[z][x][y]);
                        }
                        grid[x-cutx] = row;
                }
                TFRcube[z] = grid;
        }
        this->children[3] = Split(TFRcube, cutz, rows-cutx, cols-cuty);

	//5 BBL - Bottom Back Left
	Voxel*** BBLcube = new Voxel**[depth-cutz];
        for(int z = cutz; z < depth; z++)
        {
                Voxel** grid = new Voxel*[cutx];
                for(int x = 0; x < cutx; x++)
                {
                        Voxel* row = new Voxel[cuty];
                        for(int y = 0; y < cuty; y++)
                        {
                                row[y] = std::move(this->data[z][x][y]);
                        }
                        grid[x] = row;
                }
                BBLcube[z-cutz] = grid;
        }
        this->children[4] = Split(BBLcube, depth-cutz, cutx, cuty);

	//6 BBR - Bottom Back Right
	Voxel*** BBRcube = new Voxel**[depth-cutz];
        for(int z = cutz; z < depth; z++)
        {
                Voxel** grid = new Voxel*[cutx];
                for(int x = 0; x < cutx; x++)
                {
                        Voxel* row = new Voxel[cols-cuty];
                        for(int y = cuty; y < cols; y++)
                        {
                                row[y-cuty] = std::move(this->data[z][x][y]);
                        }
                        grid[x] = row;
                }
                BBRcube[z-cutz] = grid;
        }
        this->children[5] = Split(BBRcube, depth-cutz, cutx, cols-cuty);

	//7 BFL - Bottom Front Left
	Voxel*** BFLcube = new Voxel**[depth-cutz];
        for(int z = cutz; z < depth; z++)
        {
                Voxel** grid = new Voxel*[rows-cutx];
                for(int x = cutx; x < rows; x++)
                {
                        Voxel* row = new Voxel[cuty];
                        for(int y = 0; y < cuty; y++)
                        {
                                row[y] = std::move(this->data[z][x][y]);
                        }
                        grid[x-cutx] = row;
                }
                BFLcube[z-cutz] = grid;
        }
        this->children[6] = Split(BFLcube, depth-cutz, rows-cutx, cuty);

	//8 BFR - Bottom Front Right
	Voxel*** BFRcube = new Voxel**[depth-cutz];
        for(int z = cutz; z < depth; z++)
        {
                Voxel** grid = new Voxel*[rows-cutx];
                for(int x = cutx; x < rows; x++)
                {
                        Voxel* row = new Voxel[cols-cuty];
                        for(int y = cuty; y < cols; y++)
                        {
                                row[y-cuty] = std::move(this->data[z][x][y]);
                        }
                        grid[x-cutx] = row;
                }
                BFRcube[z-cutz] = grid;
        }
        this->children[7] = Split(BFRcube, depth-cutz, rows-cutx, cols-cuty);

	
}

//returns boundary of Split region
std::vector<Voxel> imgpro::Split::getBoundary()
{
	std::vector<Voxel> boundary;
	if(this->data != nullptr)
	{
		for(int z=0; z < this->depth; z++)
		{
			for(int x=0; x < this->rows; x++)
			{
				for(int y=0; y < this->cols; y++)
				{	
					if( (z==0) || (z==(this->depth-1)) )
					{
						boundary.push_back(this->data[z][x][y]);
					}
					else if( (x==0) || (x==(this->rows-1)) )
					{
						boundary.push_back(this->data[z][x][y]);
					}
					else if( (y==0) || (y==(this->cols-1)) )
					{
						boundary.push_back(this->data[z][x][y]);
					}
				}
			}
		}
	}
	return boundary;
}

namespace imgpro{
//prints split data, for tracing
std::ostream & operator<<(std::ostream & out, Split & s)
{
	for(int z = 0; z < s.depth; z++)
	{
		for(int x = 0; x < s.rows; x++)
        	{
                	for(int y = 0; y < s.cols; y++)
                	{
                        	out << int(s.data[z][x][y].getIntensity()) << " ";
                	}
                        out << std::endl;
		}
		out << "" << std::endl;
        }
        return out;

}}

//set ID 
void imgpro::Split::setID(int ID)
{
	this->ID = ID;
}

//not equals operator
bool imgpro::Split::operator!=(Split & s)
{
	bool ret = false;
	if(this->ID != s.ID)
	{
		ret = true;
	}
	return ret;
}
