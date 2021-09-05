/* Noah De Nicola
 * 16/08/21
 * practiceDriver.cpp
 */

#define CATCH_CONFIG_MAIN
#include "Split.h"
#include "Voxel.h"
#include "ImageProcessor.h"
#include "Fracture.h"
#include "catch.hpp"

using namespace imgdata;

TEST_CASE ("Trial")
{
	
	//construct Set
	int d(128);
	int r(128);
	int c(128);
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
	
	SECTION("Z axis")
	{

	}

	SECTION("X axis")
	{
	}

	SECTION("Y axis")
	{
	}

	SECTION("All Axes")
	{
		//make fracture 0
		for(int z = 0; z < 128; z++)
		{
			for(int x = 60; x < 61 ; x++)
			{
				for(int y = 60; y < 61; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);
				}
			}
		}

		//make fracture 1
		for(int z = 60; z < 61; z++)
		{
			for(int x = 0; x < 128 ; x++)
			{
				for(int y = 60; y < 61; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);

				}
			}
		}

		//make fracture 3
		for(int z = 60; z < 61; z++)
		{
			for(int x = 60; x < 61; x++)
			{
				for(int y = 0; y < 128; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);
				}
			}
		}
		//cube[60][60][60] = Voxel(60,60,60,1);

		
		//splitMerge
		std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);

		//print fractures
		for(std::vector<Fracture>::iterator f = frac.begin(); f != frac.end(); f++)
		{
			std::cout << *f << std::endl;
		}

		//return 0;
	       	REQUIRE(frac.size() == 1);
		REQUIRE(frac[0].getVoxels() == 382);
	}

	SECTION("All axes without origin")
	{
		//make fracture 0
		for(int z = 0; z < 128; z++)
		{
			for(int x = 60; x < 61 ; x++)
			{
				for(int y = 60; y < 61; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);
				}
			}
		}

		//make fracture 1
		for(int z = 60; z < 61; z++)
		{
			for(int x = 0; x < 128 ; x++)
			{
				for(int y = 60; y < 61; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);

				}
			}
		}

		//make fracture 3
		for(int z = 60; z < 61; z++)
		{
			for(int x = 60; x < 61; x++)
			{
				for(int y = 0; y < 128; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);
				}
			}
		}
		//cube[60][60][60] = Voxel(60,60,60,1);

		
		//splitMerge
		std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);

		//print fractures
		for(std::vector<Fracture>::iterator f = frac.begin(); f != frac.end(); f++)
		{
			std::cout << *f << std::endl;
		}

		//return 0;
	       	REQUIRE(frac.size() == 1);
		REQUIRE(frac[0].getVoxels() == 382);
	}

}

