// Header file for the Fracture class
// htciai001
// 24/08/21 

#ifndef FRACTURE_H
#define FRACTURE_H

#include <vector>
#include <string>
#include <iostream>
#include "Voxel.h"
#include "Split.h"

namespace imgdata {
    class Fracture {
        private:
            std::vector<Voxel> coords;
            int numVoxels;
            int fid;
            std::string colour;
        
        public:
            Fracture(void);
            Fracture(int id, std::string colour);

            ~Fracture();

            Fracture(const Fracture& f);
            Fracture& operator=(const Fracture& rhs);

            Fracture(Fracture&& f);
            Fracture& operator=(Fracture&& rhs);

            friend std::ostream & operator<<(std::ostream& out, Fracture& rhs);
	    bool operator>(const Fracture & rhs) const;

            int getVoxels(void) const;
            int getID(void) const;
            std::string getColour(void) const;
            std::vector<Voxel> getCoords(void) const;
	    bool meets(const Fracture & f) const;

	    void join(Fracture & f);
            void insertVoxel(imgdata::Voxel& vox);
	    void insertSplit(imgpro::Split & s); 

            void setColour(std::string colour);
    

    };
}
#endif
