/* Noah De Nicola
 * 16/08/21
 * Split.cpp
 */

#include "Split.h"

//Default
Split::Split(): data(nullptr), allFracture(NULL), someFracture(NULL), rows(0), cols(0){}

//Destructor
Split::~Split(){}

//Custom
Split::Split(std::shared_ptr<std::shared_ptr<Pixel[]>[]> & data, int rows, int cols): data(data), allFracture(NULL), someFracture(NULL), rows(rows), cols(cols){}

//Copy Constructor
Split::Split(const Split & s): data(nullptr), allFracture(s.allFracture), someFracture(s.someFracture), rows(s.rows), cols(s.cols)
{
	if(s.data != nullptr)
	{
		this->data = std::make_shared<std::shared_ptr<Pixel[]>[]> (new Pixel[this->rows]);
		for(int x = 0; x < this->rows; x++)
                {
			std::shared_ptr<Pixel[]> row(new Pixel[cols]);
                        for(int y = 0; y < this->cols; y++)
                        {
                                row[y] = s.data[x][y];
                        }
                        this->data[x] = row;
                }
	}
	for(std::vector<std::shared_ptr<Split>>::const_iterator i = s.children.begin(); i != s.children.end(); ++i)
	{
		std::shared_ptr<Split> temp = *i;
		this->children.push_back(std::make_shared<Split>(*temp));
	}
}

//Copy Assignment Operator
Split& Split::operator=(const Split & s)
{
	if(this != &s)
	{
		if(this->data != nullptr)
		{
			for(int x = 0; x < this->rows; x++)
			{
				this->data[x].reset();
			}
			this->data.reset();
		}
		this->allFracture = s.allFracture;
		this->someFracture = s.someFracture;
		this->rows = s.rows;
		this->cols = s.cols;
		
		for(std::vector<std::shared_ptr<Split>>::const_iterator i = s.children.begin(); i != s.children.end(); ++i)
        	{
			std::shared_ptr<Split> temp = *i;
                	this->children.push_back(std::make_shared<Split>(*temp));
        	}
		
		if(s.data != nullptr)
		{
			std::shared_ptr<std::shared_ptr<Pixel[]>[]> temp(new std::shared_ptr<Pixel[]>[this->rows]);
        	        for(int x = 0; x < this->rows; x++)
                	{
                        	std::shared_ptr<Pixel[]> row(new Pixel[this->cols]);
                        	for(int y = 0; y < this->cols; y++)
                        	{
                                	row[y] = s.data[x][y];
                        	}
                        	temp[x] = row;
                	}
			this->data = std::move(temp);	
		}
	}
	return *this;
}

//Move Constructor 
Split::Split(Split && s): data(nullptr), allFracture(s.allFracture), someFracture(s.someFracture), rows(s.rows), cols(s.cols)
{
	for(std::vector<std::shared_ptr<Split>>::iterator i = s.children.begin(); i != s.children.end(); ++i)
	{
                this->children.push_back(std::move(*i));
        }

	if(s.data != nullptr)
	{
		this->data = std::move(s.data);
	}
	
}

//Move Assignment Operator
Split& Split::operator=(Split && s)
{
	if (this != &s)
	{
		if(this->data != nullptr)
		{
			for(int x = 0; x < this->rows; x++)
                        {
                                this->data[x].reset();
                        }
                        this->data.reset();
		}
		if(s.data != nullptr)
		{
			this->data = std::move(s.data);
		}
		this->allFracture = s.allFracture;
		this->someFracture = s.someFracture;
                this->rows = s.rows;
                this->cols = s.cols;

		for(std::vector<std::shared_ptr<Split>>::iterator i = s.children.begin(); i != s.children.end(); ++i)
        	{
                	this->children.push_back(std::move(*i));
        	}

	}
	return *this;
}

std::vector<std::shared_ptr<Split>> Split::getKids()
{
	return this->children;
}

std::vector<int> Split::getDim()
{
	std::vector<int> ret({this->rows, this->cols});
	return ret;
}

std::shared_ptr< std::shared_ptr<Pixel[]>[] > Split::getData()
{
	return this->data;
}

void Split::test()
{
	this->someFracture = false;
	this->allFracture = true;
	for(int y=0; y < this->rows; y++)
	{
		for(int x = 0; x < this->cols; x++)
		{
			if (this->data[y][x].getIntensity() == 0)
			{
				this->someFracture = true;
			}
			if (this->data[y][x].getIntensity() != 0)
			{
				this->allFracture = false;
			}			
		}
	}
}

bool Split::getAllFrac()
{
	return this->allFracture;
}

bool Split::getSomeFrac()
{
	return this->someFracture;
}

void Split::cut()
{
	
	//get cut spot
	int cutx = cols/2;
	int cuty = rows/2;
	
		
	//4 Regions
		
	//TLeft
	std::shared_ptr<std::shared_ptr<Pixel[]>[]> tleft(new std::shared_ptr<Pixel[]>[cuty]);
	for(int x = 0; x < cuty; x++)
	{
		std::shared_ptr<Pixel[]> row(new Pixel[cutx]);
		for(int y = 0; y < cutx; y++)
		{
			row[y] = this->data[x][y];	
		}
		tleft[x] = row;
	}
	this->children.push_back(std::make_shared<Split>(tleft, cuty, cutx));
	
	//BLeft
  	std::shared_ptr<std::shared_ptr<Pixel[]>[]> bleft(new std::shared_ptr<Pixel[]>[rows-cuty]);
	for(int x = cuty; x < rows; x++)
	{
		std::shared_ptr<Pixel[]> row(new Pixel[cutx]);
		for(int y = 0; y < cutx; y++)
		{

			row[y] = this->data[x][y];
		}
		bleft[x-cuty] = row;
	}
	this->children.push_back(std::make_shared<Split>(bleft, rows-cuty, cutx));

	//TRight
	std::shared_ptr<std::shared_ptr<Pixel[]>[]> tright(new std::shared_ptr<Pixel[]>[cuty]);
	for(int x = 0; x < cuty; x++)
	{
		std::shared_ptr<Pixel[]> row(new Pixel[cols-cutx]);
		for(int y = cutx; y < cols; y++)
		{
			row[y-cutx] = this->data[x][y];
		}
		tright[x] = row;
	}
	this->children.push_back(std::make_shared<Split>(tright, cuty, cols-cutx));

	//BRight
	std::shared_ptr<std::shared_ptr<Pixel[]>[]> bright(new std::shared_ptr<Pixel[]>[rows-cuty]);
	for(int x = cuty; x < rows; x++)
	{
		std::shared_ptr<Pixel[]> row(new Pixel[cols-cutx]);
		for(int y = cutx; y < cols; y++)
		{
			row[y-cutx] = this->data[x][y];
		}
		bright[x-cuty] = row;
	}
	this->children.push_back(std::make_shared<Split>(bright, rows-cuty, cols-cutx));

	//delete parent data
	for(int x = 0; x < this->rows; x++)
	{
		this->data[x].reset();
	}
	this->data.reset();
}

std::ostream & operator<<(std::ostream & out, Split & s)
{
	for(int x = 0; x < s.rows; x++)
        {
                for(int y = 0; y < s.cols; y++)
                {
                        out << int(s.data[x][y].getIntensity()) << " ";
                }
                if(x < s.rows-1)
                {
                        out << std::endl;
                }
        }
        return out;

}
