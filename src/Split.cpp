/* Noah De Nicola
 * 16/08/21
 * Split.cpp
 */

#include "Split.h"
using namespace imgdata;
//Default
imgpro::Split::Split(): data(nullptr), allFracture(NULL), someFracture(NULL), depth(0), rows(0), cols(0), ID(-1){}

//Destructor
imgpro::Split::~Split()
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
}

//Custom
imgpro::Split::Split(Voxel*** & data, int depth, int rows, int cols): data(data), allFracture(NULL), someFracture(NULL), depth(depth), rows(rows), cols(cols), ID(-1){}

//Copy Constructor
imgpro::Split::Split(const Split & s): data(nullptr), allFracture(s.allFracture), someFracture(s.someFracture), depth(s.depth), rows(s.rows), cols(s.cols), ID(s.ID)
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
	for(std::vector<std::shared_ptr<imgpro::Split>>::const_iterator i = s.children.begin(); i != s.children.end(); ++i)
	{
		std::shared_ptr<imgpro::Split> temp = *i;
		this->children.push_back(std::make_shared<imgpro::Split>(*temp));
	}
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

		this->allFracture = s.allFracture;
		this->someFracture = s.someFracture;
		this->depth = s.depth;
		this->rows = s.rows;
		this->cols = s.cols;
		this->ID = s.ID;
		
		for(std::vector<std::shared_ptr<imgpro::Split>>::const_iterator i = s.children.begin(); i != s.children.end(); ++i)
        	{
			std::shared_ptr<imgpro::Split> temp = *i;
                	this->children.push_back(std::make_shared<imgpro::Split>(*temp));
        	}
		
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
imgpro::Split::Split(imgpro::Split && s): data(nullptr), allFracture(s.allFracture), someFracture(s.someFracture), depth(s.depth), rows(s.rows), cols(s.cols), ID(s.ID)
{
	for(std::vector<std::shared_ptr<imgpro::Split>>::iterator i = s.children.begin(); i != s.children.end(); ++i)
	{
                this->children.push_back(std::move(*i));
        }

	if(s.data != nullptr)
	{
		this->data = std::move(s.data);
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
		if(s.data != nullptr)
		{
			this->data = std::move(s.data);
		}
		this->allFracture = s.allFracture;
		this->someFracture = s.someFracture;
		this->depth = s.depth;
                this->rows = s.rows;
                this->cols = s.cols;
		this->ID = s.ID;

		for(std::vector<std::shared_ptr<imgpro::Split>>::iterator i = s.children.begin(); i != s.children.end(); ++i)
        	{
                	this->children.push_back(std::move(*i));
        	}

	}
	return *this;
}

std::vector<std::shared_ptr<imgpro::Split>> imgpro::Split::getKids()
{
	return this->children;
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

std::vector<int> imgpro::Split::getDim()
{
	std::vector<int> ret({this->rows, this->cols, this->depth});
	return ret;
}

int imgpro::Split::getDepth()
{
	return this->depth;
}

int imgpro::Split::getRows()
{
	return this->rows;
}

int imgpro::Split::getCols()
{
	return this->cols;
}

int imgpro::Split::getID()
{
	return this->ID;
}

Voxel*** imgpro::Split::getData()
{
	return this->data;
}

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

bool imgpro::Split::getAllFrac()
{
	return this->allFracture;
}

bool imgpro::Split::getSomeFrac()
{
	return this->someFracture;
}

void imgpro::Split::cut()
{
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
				row[y] = this->data[z][x][y];	
			}
			grid[x] = row;
		}
		TBLcube[z] = grid;
	}
	this->children.push_back(std::make_shared<imgpro::Split>(TBLcube, cutz, cutx, cuty));

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
                                row[y-cuty] = this->data[z][x][y];
                        }
                        grid[x] = row;
                }
                TBRcube[z] = grid;
        }
        this->children.push_back(std::make_shared<imgpro::Split>(TBRcube, cutz, cutx, cols-cuty)); 
	
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
                                row[y] = this->data[z][x][y];
                        }
                        grid[x-cutx] = row;
                }
                TFLcube[z] = grid;
        }
        this->children.push_back(std::make_shared<imgpro::Split>(TFLcube, cutz, rows-cutx, cuty));
	
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
                                row[y-cuty] = this->data[z][x][y];
                        }
                        grid[x-cutx] = row;
                }
                TFRcube[z] = grid;
        }
        this->children.push_back(std::make_shared<imgpro::Split>(TFRcube, cutz, rows-cutx, cols-cuty));

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
                                row[y] = this->data[z][x][y];
                        }
                        grid[x] = row;
                }
                BBLcube[z-cutz] = grid;
        }
        this->children.push_back(std::make_shared<imgpro::Split>(BBLcube, depth-cutz, cutx, cuty));

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
                                row[y-cuty] = this->data[z][x][y];
                        }
                        grid[x] = row;
                }
                BBRcube[z-cutz] = grid;
        }
        this->children.push_back(std::make_shared<imgpro::Split>(BBRcube, depth-cutz, cutx, cols-cuty));

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
                                row[y] = this->data[z][x][y];
                        }
                        grid[x-cutx] = row;
                }
                BFLcube[z-cutz] = grid;
        }
        this->children.push_back(std::make_shared<imgpro::Split>(BFLcube, depth-cutz, rows-cutx, cuty));

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
                                row[y-cuty] = this->data[z][x][y];
                        }
                        grid[x-cutx] = row;
                }
                BFRcube[z-cutz] = grid;
        }
        this->children.push_back(std::make_shared<imgpro::Split>(BFRcube, depth-cutz, rows-cutx, cols-cuty));


	
}

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


void imgpro::Split::setID(int ID)
{
	this->ID = ID;
}

bool imgpro::Split::operator!=(Split & s)
{
	bool ret = false;
	if(this->ID != s.ID)
	{
		ret = true;
	}
	return ret;
}
