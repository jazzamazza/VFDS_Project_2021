#include "ImageProcessor.h"
#include "Fracture.h"
#include <vector>

int main(void)
{
	using namespace imgdata;
	//construct Set
	int d(5);
	int r(5);
	int c(5);
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

	int x(4);
	int y(4);
	int z(0);
	for(int i = 0; i < 5; i++)
	{
		cube[z][x][y] = Voxel(x,y,z,0);
		if(z < 4)
		{
			cube[z+1][x][y] = Voxel(x,y,z+1,0);
		}
		if(y>0)
		{
		//	cube[z][x][y-1] = Voxel(x,y-1,z,0);
		}	
		x--,y--,z++;

	}	
	std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);
	for(std::vector<Fracture>::iterator i = frac.begin(); i != frac.end(); ++i)
	{
		std::cout << *i << std::endl;
	}

}
