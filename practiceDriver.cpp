/* Noah De Nicola
 * 16/08/21
 * practiceDriver.cpp
 */

#include "Split.h"
#include "Voxel.h"
#include "ImageProcessor.h"
#include "Fracture.h"

int main(void)
{
	using namespace imgdata;
	//construct Set
	int d = 5;
	int r = 5;
	int c = 5;

	Voxel*** cube = new Voxel**[d];
	for(int z = 0; z < d; z++)
	{
		Voxel** set = new Voxel*[r];
		for(int x = 0; x < r; x++)
		{
			Voxel * row = new Voxel[c];
			for(int y = 0; y < c; y++)
			{
				row[y] = Voxel(x,y,z,1);
			}
			set[x] = row;
		}
		cube[z] = set;
	}

	//make fracture 0
	for(int z = 0; z < 5; z++)
        {
                for(int x = 1; x < 3 ; x++)
                {
                        for(int y = 1; y < 3; y++)
                        {
                                cube[z][x][y] = Voxel(x,y,z,0);
                        }
                }
        }

	/*make fracture 1 uncomment to see logic error
	for(int z = 3; z < 5; z++)
        {
                for(int x = 3; x < 5 ; x++)
                {
                        for(int y = 0; y < 5; y++)
                        {
                                cube[z][x][y] = Voxel(x,y,z,0);
                        }
                }
        }*/

	std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);
}
