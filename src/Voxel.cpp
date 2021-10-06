// Voxel class to represent 3d image data
// htciai001
// 24/08/21

#include "Voxel.h"

// default constructor
imgdata::Voxel::Voxel(void) : x(-1), y(-1), z(-1), intensity(0) {}
// custom constructor
imgdata::Voxel::Voxel(int x, int y, int z, unsigned char intensity) : x(x), y(y), z(z), intensity(intensity) {}

imgdata::Voxel::~Voxel() {}

// copy constructor
imgdata::Voxel::Voxel(const Voxel& v) : x(v.x), y(v.y), z(v.z), intensity(v.intensity) {}

// copy assignment operator
imgdata::Voxel& imgdata::Voxel::operator=(const imgdata::Voxel& rhs) {
    // ensure that this is not self-assignment
    if(this != &rhs) {
        this->intensity = rhs.intensity;

        this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
    }

    return *this;
}

// move constructor
imgdata::Voxel::Voxel(imgdata::Voxel&& v) : x(v.x), y(v.y), z(v.z), intensity(v.intensity) {
    v.x = -1;
    v.y = -1;
    v.z = -1;
    v.intensity = 0;
}

imgdata::Voxel& imgdata::Voxel::operator=(imgdata::Voxel&& rhs) {
    // ensure that this is not self-assignment
    if(this != &rhs) {
        this->intensity = rhs.intensity;
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
       
	rhs.x = -1;
	rhs.y = -1;
	rhs.z = -1;
        rhs.intensity = 0;
    }

    return *this;
}

const unsigned char imgdata::Voxel::getIntensity() const {
    return this->intensity;
}

const int imgdata::Voxel::getX() const{
    return this->x;
}

const int imgdata::Voxel::getY() const{
    return this->y;
}

const int imgdata::Voxel::getZ() const {
    return this->z;
}

imgdata::Voxel imgdata::Voxel::operator+(const Voxel & v)
{
	Voxel temp(*this);
	temp.x += v.x;
	temp.y += v.y;
	temp.z += v.z;

	return temp;
}
namespace imgdata{
std::ostream & operator<<(std::ostream & out, const Voxel & v)
{
	out << "(" << v.x << ", " << v.y << ", " << v.z << ")";   
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
	if( (temp.x == v.x) && (temp.y == v.y) && (temp.z == v.z) )
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
