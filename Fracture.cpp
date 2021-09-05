// Fracture class to store the identified fractures from the VFDS
// htciai001
// 24/08/21 

#include "Fracture.h"

// default constructor
imgdata::Fracture::Fracture(void) : coords(std::vector<imgdata::Voxel>()), numVoxels(0), fid(-1), colour("null") {}
// custom constructor
imgdata::Fracture::Fracture(int id, std::string colour) : coords(std::vector<imgdata::Voxel>()), numVoxels(0), fid(id), colour(colour) {}

// destructor
imgdata::Fracture::~Fracture() {}

// copy constructor
imgdata::Fracture::Fracture(const imgdata::Fracture& f) : coords(f.coords), numVoxels(f.numVoxels), fid(f.fid), colour(f.colour) {}
// copy assignment operator
imgdata::Fracture& imgdata::Fracture::operator=(const imgdata::Fracture& rhs) {
    
    if(this != &rhs) {
        this->numVoxels = rhs.numVoxels;
        this->fid = rhs.fid;
        this->colour = rhs.colour;

        // clears coordinate vector if already containing data
        if(!this->coords.empty()) {
            coords.clear();
        }

        if(!rhs.coords.empty())
            this->coords = rhs.coords;
    }
    return *this;
}

// move constructor
imgdata::Fracture::Fracture(Fracture&& f) : coords(f.coords), numVoxels(f.numVoxels), fid(f.fid), colour(f.colour) {
        
    // clear the rhs vector of all coordinate values
    f.coords.clear();

    // set number of pixels to 0 and id to -1
    f.numVoxels = 0;
    f.fid = -1;
    f.colour = "null";

}
// move assignment operator
imgdata::Fracture& imgdata::Fracture::operator=(imgdata::Fracture&& rhs) {
    // prevent self-assignment
    if(this != &rhs) {
        this->numVoxels = rhs.numVoxels;
        this->fid = rhs.fid;

        if(!this->coords.empty()) {
            this->coords.clear();
        }

        if(!rhs.coords.empty()) {
            this->coords = rhs.coords;
            rhs.coords.clear();
        }

        rhs.numVoxels = 0;
        rhs.fid = -1;
        rhs.colour = "null";
    }
    return *this;
}

namespace imgdata {
// output stream operator overload
    std::ostream & operator<<(std::ostream& out, imgdata::Fracture& rhs) {
        if(rhs.getID()==-1)
	{
            out << "null" << std::endl;
	}
        else
	{
        	out << "Fracture ID: " << rhs.getID() << ", Number of voxels: " << rhs.getVoxels();
		/*for(std::vector<Voxel>::iterator i = rhs.coords.begin(); i != rhs.coords.end(); ++i)
		{
			std::cout << "("  << i->getX() << "," << i->getY() << "," << i->getZ() << ")" << std::endl;
		}*/
	}	    	
		
        
        return out;
    }
}

int imgdata::Fracture::getVoxels(void) const {
    return this->numVoxels;
}

int imgdata::Fracture::getID(void) const {
    return this->fid;
}

std::string imgdata::Fracture::getColour(void) const {
    return this->colour;
}

std::vector<imgdata::Voxel> imgdata::Fracture::getCoords(void) const {
    return this->coords;
}

// insert a voxel into a fracture object
void imgdata::Fracture::insertVoxel(imgdata::Voxel& vox) {

    // add voxel to the vector of coordinates
    this->coords.push_back(vox);

    //increment the count of pixels
    this->numVoxels++;
}

void imgdata::Fracture::join(Fracture & f)
{
	for(std::vector<Voxel>::iterator i = f.coords.begin(); i != f.coords.end(); ++i)
	{
		this->insertVoxel(*i);
	}
}

void imgdata::Fracture::insertSplit(Split & s)
{
	imgdata::Voxel*** data = s.getData();
	std::vector<int> d = s.getDim();

	for(int z = 0; z < d[2]; z++)
	{
		for(int x = 0; x < d[0]; x++)
		{
			for(int y = 0; y < d[1]; y++)
			{
				this->insertVoxel(data[z][x][y]);
			}
		}
	}
}
