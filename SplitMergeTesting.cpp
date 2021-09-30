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

TEST_CASE ("Axes")
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
				row[y] = Voxel(x,y,z,250);
			}
			set[x] = row;
		}
		cube[z] = set;
	}

	
	SECTION("Z-axis")
	{
		std::cout << "Test Case: Axes\n" << d << "x" << r  << "x" << c << " cube constructed." << std::endl; 
		std::cout << "\nZ Axis..." << std::endl;
		//z
		for(int z = 0; z < 128; z++)
		{
			for(int x = 64; x < 65 ; x++)
			{
				for(int y = 64; y < 65; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);
				}
			}
		}
		
		//splitMerge
		std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);

		//print fractures
		/*for(std::vector<Fracture>::iterator f = frac.begin(); f != frac.end(); f++)
		{
			std::cout << *f << std::endl;
		}*/

	       	REQUIRE(frac.size() == 1);
		REQUIRE(frac[0].getVoxels() == 128);

		std::cout << "pass!" << std::endl;
	}

	SECTION("X-axis")
	{
		std::cout << "X Axis..." << std::endl;
		//x
		for(int z = 64; z < 65; z++)
		{
			for(int x = 0; x < 128 ; x++)
			{
				for(int y = 64; y < 65; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);

				}
			}
		}

		//splitMerge
		std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);

		//print fractures
		/*for(std::vector<Fracture>::iterator f = frac.begin(); f != frac.end(); f++)
		{
			std::cout << *f << std::endl;
		}*/

	       	REQUIRE(frac.size() == 1);
		REQUIRE(frac[0].getVoxels() == 128);

		std::cout << "pass!" << std::endl;
	}

	SECTION("Y-axis")
	{
		std::cout << "Y-Axis..." << std::endl;

		//y
		for(int z = 64; z < 65; z++)
		{
			for(int x = 64; x < 65; x++)
			{
				for(int y = 0; y < 128; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);
				}
			}
		}

		//splitMerge
		std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);

		//print fractures
		/*for(std::vector<Fracture>::iterator f = frac.begin(); f != frac.end(); f++)
		{
			std::cout << *f << std::endl;
		}*/

	       	REQUIRE(frac.size() == 1);
		REQUIRE(frac[0].getVoxels() == 128);

		std::cout << "pass!" << std::endl;
	}

	SECTION("All Axes")
	{
		std::cout << "All Axes..." << std::endl;
		//z
		for(int z = 0; z < 128; z++)
		{
			for(int x = 64; x < 65; x++)
			{
				for(int y = 64; y < 65; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);
				}
			}
		}

		//x
		for(int z = 64; z < 65; z++)
		{
			for(int x = 0; x < 128 ; x++)
			{
				for(int y = 64; y < 65; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);

				}
			}
		}

		//y
		for(int z = 64; z < 65; z++)
		{
			for(int x = 64; x < 65; x++)
			{
				for(int y = 0; y < 128; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);
				}
			}
		}

		
		//splitMerge
		std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);

		//print fractures
		/*for(std::vector<Fracture>::iterator f = frac.begin(); f != frac.end(); f++)
		{
			std::cout << *f << std::endl;
		}*/

		//return 0;
	       	REQUIRE(frac.size() == 1);
		REQUIRE(frac[0].getVoxels() == 382);

		std::cout << "pass!" << std::endl;
	}

	SECTION("All axes without origin")
	{
		std::cout << "All axes without origin..." << std::endl;
			

		//make fracture 0
		for(int z = 0; z < 128; z++)
		{
			for(int x = 64; x < 65 ; x++)
			{
				for(int y = 64; y < 65; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);
				}
			}
		}
		//make fracture 1
		for(int z = 64; z < 65; z++)
		{
			for(int x = 0; x < 128 ; x++)
			{
				for(int y = 64; y < 65; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);

				}
			}
		}

		//make fracture 3
		for(int z = 64; z < 65; z++)
		{
			for(int x = 64; x < 65; x++)
			{
				for(int y = 0; y < 128; y++)
				{
					cube[z][x][y] = Voxel(x,y,z,0);
				}
			}
		}
		cube[64][64][64] = Voxel(64,64,64,250);

		
		//splitMerge
		std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);

		/*print fractures
		for(std::vector<Fracture>::iterator f = frac.begin(); f != frac.end(); f++)
		{
			std::cout << *f << std::endl;
		}*/

	       	REQUIRE(frac.size() == 6);
		REQUIRE(frac[0].getVoxels() == 64);
		REQUIRE(frac[1].getVoxels() == 64);
		REQUIRE(frac[2].getVoxels() == 64);
		REQUIRE(frac[3].getVoxels() == 63);
		REQUIRE(frac[4].getVoxels() == 63);
		REQUIRE(frac[5].getVoxels() == 63);


		std::cout << "pass!\n\nTest Case: Axes - pass!" << std::endl;
	}


}

TEST_CASE("Diagonals")
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
				row[y] = Voxel(x,y,z,250);
			}
			set[x] = row;
		}
		cube[z] = set;
	}

	SECTION("(0,0,0) <-> (127,127,127)")
	{
		std::cout << "\nTest Case: Diagonals\n" << d << "x" << r  << "x" << c << " cube constructed." << std::endl; 
		std::cout << "\n(0,0,0) <-> (127,127,127)..." << std::endl;	

		int x(0);
		int y(0);
		int z(0);
		for(int i = 0; i < 128; i++)
		{
			cube[z][x][y] = Voxel(x,y,z,0);
			if(z < 127)
			{
				cube[z+1][x][y] = Voxel(x,y,z+1,0);
			}
			if(y>0)
			{
				cube[z][x][y-1] = Voxel(x,y-1,z,0);
			}	
			x++,y++,z++;

		}		
		std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);
		REQUIRE(frac.size() == 1);
		REQUIRE(frac[0].getVoxels() == 382);
		std::cout << "pass!" << std::endl;
	}

	SECTION("(127,127,0) <-> (0,0,127)")
	{
		std::cout << "(127,127,0) <-> (0,0,127)..." << std::endl;	
		int x(127);
		int y(127);
		int z(0);
		for(int i = 0; i < 128; i++)
		{
			cube[z][x][y] = Voxel(x,y,z,0);
			if(z < 127)
			{
				cube[z+1][x][y] = Voxel(x,y,z+1,0);
			}
			if(y < 127)
			{
				cube[z][x][y+1] = Voxel(x,y+1,z,0);
			}	
			x--,y--,z++;

		}		
		std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);
		REQUIRE(frac.size() == 1);
		REQUIRE(frac[0].getVoxels() == 382);
		std::cout << "pass!" << std::endl;
	}

	SECTION("(127,0,0) <-> (0,127,127)")
	{
		std::cout << "(127,0,0) <-> (0,127,127)..." << std::endl;	
		int x(127);
		int y(0);
		int z(0);
		for(int i = 0; i < 128; i++)
		{
			cube[z][x][y] = Voxel(x,y,z,0);
			if(z < 127)
			{
				cube[z+1][x][y] = Voxel(x,y,z+1,0);
			}
			if(y>0)
			{
				cube[z][x][y-1] = Voxel(x,y-1,z,0);
			}	
			x--,y++,z++;

		}		
		std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);
		REQUIRE(frac.size() == 1);
		REQUIRE(frac[0].getVoxels() == 382);
		std::cout << "pass!" << std::endl;
	}

	SECTION("(0,127,0) <-> (127,0,127)")
	{
		std::cout << "(0,127,0) <-> (127,0,127)..." << std::endl;	
		int x(0);
		int y(127);
		int z(0);
		for(int i = 0; i < 128; i++)
		{
			cube[z][x][y] = Voxel(x,y,z,0);
			if(z < 127)
			{
				cube[z+1][x][y] = Voxel(x,y,z+1,0);
			}
			if(y < 127)
			{
				cube[z][x][y+1] = Voxel(x,y+1,z,0);
			}	
			x++,y--,z++;

		}		
		std::vector<Fracture> frac = func::splitMerge(cube, r, c, d);
		REQUIRE(frac.size() == 1);
		REQUIRE(frac[0].getVoxels() == 382);
		std::cout << "pass!\n\nTest Case: Diagonals - pass!" << std::endl;
		std::cout << "\nTesting complete." << std::endl;
	}
}

