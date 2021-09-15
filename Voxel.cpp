// Voxel class to represent 3d image data
// htciai001
// 24/08/21

#include "Voxel.h"

// default constructor
imgdata::Voxel::Voxel(void) : coords(std::vector<int>()), intensity(0) {}
// custom constructor
imgdata::Voxel::Voxel(int x, int y, int z, unsigned char intensity) : intensity(intensity), coords(std::vector<int>()) {
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(z);
}

imgdata::Voxel::~Voxel() {}

// copy constructor
imgdata::Voxel::Voxel(const Voxel& v) : coords(v.coords), intensity(v.intensity) {}

// copy assignment operator
imgdata::Voxel& imgdata::Voxel::operator=(const imgdata::Voxel& rhs) {
    // ensure that this is not self-assignment
    if(this != &rhs) {
        this->intensity = rhs.intensity;

        if(!this->coords.empty()) {
            coords.clear();
        }

        if(!rhs.coords.empty())
            this->coords = rhs.coords;
    }

    return *this;
}

// move constructor
imgdata::Voxel::Voxel(imgdata::Voxel&& v) : coords(v.coords), intensity(v.intensity) {
    v.coords.clear();
    v.intensity = 0;
}

imgdata::Voxel& imgdata::Voxel::operator=(imgdata::Voxel&& rhs) {
    // ensure that this is not self-assignment
    if(this != &rhs) {
        this-> intensity = rhs.intensity;

        if(!this->coords.empty()) {
            this->coords.clear();
        }

        if(!rhs.coords.empty()) {
            this->coords = rhs.coords;
            rhs.coords.clear();
        }

        rhs.intensity = 0;
    }

    return *this;
}

const std::vector<int> imgdata::Voxel::getCoords() const{
    return this->coords;
}

const unsigned char imgdata::Voxel::getIntensity() const {
    return this->intensity;
}

const int imgdata::Voxel::getX() const{
    if(coords.size()==3)
        return this->coords[0];
    else
        return -1;
}

const int imgdata::Voxel::getY() const{
    if(coords.size()==3)
        return this->coords[1];
    else
        return -1;
}

const int imgdata::Voxel::getZ() const {
    if(coords.size()==3)
        return this->coords[2];
    else
        return -1;
}

imgdata::Voxel imgdata::Voxel::operator+(const Voxel & v)
{
	Voxel temp(*this);
	temp.coords[0] += v.coords[0];
	temp.coords[1] += v.coords[1];
	temp.coords[2] += v.coords[2];

	return temp;
}
namespace imgdata{
std::ostream & operator<<(std::ostream & out, const Voxel & v)
{
	out << "(" << v.coords[0] << ", " << v.coords[1] << ", " << v.coords[2] << ")-> " << int(v.intensity);   
	return out;
}
}
bool imgdata::Voxel::operator>(const imgdata::Voxel & v) const
{
	int rx = this->getX();
	int ry = this->getY();
	int rz = this->getZ();
	int lx = v.getX();
	int ly = v.getY();
	int lz = v.getZ();
	bool ret = false;
	if(rx*rx + ry*ry + rz*rz > lx*lx + ly*ly + lz*lz)
	{
		ret = true;
	}
	return ret;
}	

bool imgdata::Voxel::operator==(const imgdata::Voxel & v) const
{
	Voxel temp(*this);
	bool ret = false;
	if( (temp.coords[0] == v.coords[0]) && (temp.coords[1] == v.coords[1]) && (temp.coords[2] == v.coords[2]) && (temp.intensity == v.intensity) )
	{
		ret = true;
	}

	return ret;
}

//global
std::vector<imgdata::Voxel> directions = {imgdata::Voxel(1,0,0,0), imgdata::Voxel(-1,0,0,0), imgdata::Voxel(0,1,0,0), imgdata::Voxel(0,-1,0,0), imgdata::Voxel(0,0,1,0), imgdata::Voxel(0,0,-1,0)};

bool imgdata::Voxel::touching(const imgdata::Voxel & v) const
{
	std::vector<imgdata::Voxel> aNeighbours;
	bool ret = false;
	for(std::vector<imgdata::Voxel>::iterator i = directions.begin(); i != directions.end(); i++)
	{
		aNeighbours.push_back(*i + *this);
	}
	for(std::vector<imgdata::Voxel>::iterator i = aNeighbours.begin(); i != aNeighbours.end(); ++i)
	{
		imgdata::Voxel temp(*i);
		if(v == temp)
		{
			ret = true;
		}
	}
	return ret;	
	
}
