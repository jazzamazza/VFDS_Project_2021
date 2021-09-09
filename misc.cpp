#include "ImageProcessor.h"
#include "Fracture.h"
#include <vector>

int main(void)
{
	using namespace imgdata;
	//construct Set
	int d(5);
	int r(11);
	int c(11);
	Voxel*** cube = new Voxel**[d];
	for(int z = 0; z < d; z++)
	{
		Voxel** set = new Voxel*[r];
		for(int x = 0; x < r; x++)
		{
			Voxel * row = new Voxel[c];
			for(int y = 0; y < c; y++)
			{
				if(11 > (x-5)*(x-5) + (y-5)*(y-5))
				{
					if((z!=0)&&(z!=d-1))
					{
						row[y] = Voxel(x,y,z,1);
					}
				}
				else
				{
					row[y] = Voxel(x,y,z,0);
				}
					
			}
			set[x] = row;
		}
		cube[z] = set;
	}
	//make fracture
	for(int z = 2; z < 3; z++)
	{
		Voxel** set = new Voxel*[r];
		for(int x = 0; x < r; x++)
		{
			Voxel * row = new Voxel[c];
			for(int y = 5; y < 6; y++)
			{
				cube[z][x][y] = Voxel(x,y,z,0);
			}
		}
	
	}
	//print
	for(int z = 0; z < d; z++)
        {
                for(int x = 0; x < r; x++)
                {
                        for(int y = 0; y < c; y++)
                        {
				std::cout << int(cube[z][x][y].getIntensity()) << " ";
			}
			std::cout << "\n";
                }
		std::cout << "\n";
        }
	

	func::paintBackground(cube,11,11,5);
	Split s1(cube,d,r,c);
	std::cout << s1 << std::endl;

}
