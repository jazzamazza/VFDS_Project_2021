// unit testing file for the imgdata and imgread namespaces for the VFDS
// htciai001
// 26/08/21

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "src/CTReader.h"
#include "src/BackgroundData.h"
#include "src/PartData.h"
#include "src/Voxel.h"
#include "src/Fracture.h"
#include "src/Split.h"

TEST_CASE ("imgdata: Voxel class") {
    SECTION("Default Constructor") {
        imgdata::Voxel v = imgdata::Voxel();
        REQUIRE(v.imgdata::Voxel::getIntensity() == 0);
        REQUIRE(v.imgdata::Voxel::getX() == -1);
        REQUIRE(v.imgdata::Voxel::getY() == -1);
        REQUIRE(v.imgdata::Voxel::getZ() == -1);
    }

    SECTION("Custom Constructor") {
        imgdata::Voxel v = imgdata::Voxel(1,2,3,155.0);
        REQUIRE(v.imgdata::Voxel::getIntensity() == 155.0);
        REQUIRE(v.imgdata::Voxel::getX() == 1);
        REQUIRE(v.imgdata::Voxel::getY() == 2);
        REQUIRE(v.imgdata::Voxel::getZ() == 3);
    }

    SECTION("Copy Constructor") {
        imgdata::Voxel v = imgdata::Voxel(1,2,3,155.0);
        imgdata::Voxel vcpy(v);
        REQUIRE(vcpy.imgdata::Voxel::getIntensity() == 155.0);
        REQUIRE(vcpy.imgdata::Voxel::getX() == 1);
        REQUIRE(vcpy.imgdata::Voxel::getY() == 2);
        REQUIRE(vcpy.imgdata::Voxel::getZ() == 3);
    }
    
    SECTION("Copy Assignment Operator") {
        imgdata::Voxel v = imgdata::Voxel(1,2,3,155.0);
        imgdata::Voxel vcpy = v;
        REQUIRE(vcpy.imgdata::Voxel::getIntensity() == 155.0);
        REQUIRE(vcpy.imgdata::Voxel::getX() == 1);
        REQUIRE(vcpy.imgdata::Voxel::getY() == 2);
        REQUIRE(vcpy.imgdata::Voxel::getZ() == 3);
    }

    SECTION("Move Constructor") {
        imgdata::Voxel v = imgdata::Voxel(1,2,3,155.0);
        imgdata::Voxel vcpy(std::move(v));
        REQUIRE(vcpy.imgdata::Voxel::getIntensity() == 155.0);
        REQUIRE(vcpy.imgdata::Voxel::getX() == 1);
        REQUIRE(vcpy.imgdata::Voxel::getY() == 2);
        REQUIRE(vcpy.imgdata::Voxel::getZ() == 3);

        REQUIRE(v.imgdata::Voxel::getIntensity() == 0);
        REQUIRE(v.imgdata::Voxel::getX() == -1);
        REQUIRE(v.imgdata::Voxel::getY() == -1);
        REQUIRE(v.imgdata::Voxel::getZ() == -1);
    }

    SECTION("Move Assignment Operator") {
        imgdata::Voxel v = imgdata::Voxel(1,2,3,155.0);
        imgdata::Voxel vcpy = std::move(v);
        REQUIRE(vcpy.imgdata::Voxel::getIntensity() == 155.0);
        REQUIRE(vcpy.imgdata::Voxel::getX() == 1);
        REQUIRE(vcpy.imgdata::Voxel::getY() == 2);
        REQUIRE(vcpy.imgdata::Voxel::getZ() == 3);

        REQUIRE(v.imgdata::Voxel::getIntensity() == 0);
        REQUIRE(v.imgdata::Voxel::getX() == -1);
        REQUIRE(v.imgdata::Voxel::getY() == -1);
        REQUIRE(v.imgdata::Voxel::getZ() == -1);
    }
    
}

TEST_CASE ("imgdata: BackgroundData class") {

    SECTION("Default Constructor") {
        imgdata::BackgroundData bd = imgdata::BackgroundData();
        REQUIRE(bd.imgdata::BackgroundData::getIntensity() == 0.0);
        REQUIRE(bd.imgdata::BackgroundData::getDim() == 0);
    }

    SECTION("Custom Constructor") {
        imgdata::BackgroundData bd = imgdata::BackgroundData(155.0,128);
        REQUIRE(bd.imgdata::BackgroundData::getIntensity() == 155.0);
        REQUIRE(bd.imgdata::BackgroundData::getDim() == 128);
    }
}

TEST_CASE ("imgdata: PartData class") {
    SECTION("Default Constructor") {
        imgdata::PartData pd = imgdata::PartData();
        REQUIRE(pd.imgdata::PartData::getIntensity() == 0.0);
        // test that the vector of voxels is initialised to be empty by default
        auto testshape = pd.imgdata::PartData::getShape();
        REQUIRE(testshape.empty());
    }

    SECTION("Custom Constructor") {
        std::vector<imgdata::Voxel> voxvec({imgdata::Voxel(1,2,3,155.0), imgdata::Voxel(4,5,6,255.0)});
        imgdata::PartData pd = imgdata::PartData(155.0,voxvec);
        REQUIRE(pd.imgdata::PartData::getIntensity() == 155.0);
        // Test that the vector of voxels initialises correctly
        auto testshape = pd.imgdata::PartData::getShape();
        // test that the voxel at index 0 is correct
        REQUIRE(testshape[0].imgdata::Voxel::getIntensity() == 155.0);
        REQUIRE(testshape[0].imgdata::Voxel::getX() == 1);
        REQUIRE(testshape[0].imgdata::Voxel::getY() == 2);
        REQUIRE(testshape[0].imgdata::Voxel::getZ() == 3);
        // test that the voxel at index 1 is correct
        REQUIRE(testshape[1].imgdata::Voxel::getIntensity() == 255.0);
        REQUIRE(testshape[1].imgdata::Voxel::getX() == 4);
        REQUIRE(testshape[1].imgdata::Voxel::getY() == 5);
        REQUIRE(testshape[1].imgdata::Voxel::getZ() == 6);
    }
}

TEST_CASE ("imgdata: Fracture class") {
    SECTION("Default Constructor") {
        imgdata::Fracture f = imgdata::Fracture();
        REQUIRE(f.imgdata::Fracture::getVoxels() == 0);
        REQUIRE(f.imgdata::Fracture::getID() == -1);
        REQUIRE(f.getColour() == "null");

         // Test that the coords vector of voxels initialises correctly
        auto testcoords = f.imgdata::Fracture::getCoords();
        REQUIRE(testcoords.empty());
    }

    SECTION("Custom Constructor") {
        imgdata::Fracture f = imgdata::Fracture(1, (std::string)"blue");
        // populate the vector of coords with 2 Voxels
        imgdata::Voxel v1(1,2,3,155.0);
        imgdata::Voxel v2(4,5,6,255.0);
        f.imgdata::Fracture::insertVoxel(v1);
        f.imgdata::Fracture::insertVoxel(v2);

        REQUIRE(f.imgdata::Fracture::getVoxels() == 2);
        REQUIRE(f.imgdata::Fracture::getID() == 1);
        REQUIRE(f.imgdata::Fracture::getColour() == "blue");

        // Test that the coords vector of voxels initialises correctly
        auto testcoords = f.imgdata::Fracture::getCoords();
        // test that the voxel at index 0 is correct
        REQUIRE(testcoords[0].imgdata::Voxel::getIntensity() == 155.0);
        REQUIRE(testcoords[0].imgdata::Voxel::getX() == 1);
        REQUIRE(testcoords[0].imgdata::Voxel::getY() == 2);
        REQUIRE(testcoords[0].imgdata::Voxel::getZ() == 3);
        // test that the voxel at index 1 is correct
        REQUIRE(testcoords[1].imgdata::Voxel::getIntensity() == 255.0);
        REQUIRE(testcoords[1].imgdata::Voxel::getX() == 4);
        REQUIRE(testcoords[1].imgdata::Voxel::getY() == 5);
        REQUIRE(testcoords[1].imgdata::Voxel::getZ() == 6);
    }

    SECTION("Copy Constructor") {
        imgdata::Fracture f = imgdata::Fracture(1, (std::string)"blue");
        // populate the vector of coords with 2 Voxels
        imgdata::Voxel v1(1,2,3,155.0);
        imgdata::Voxel v2(4,5,6,255.0);
        f.imgdata::Fracture::insertVoxel(v1);
        f.imgdata::Fracture::insertVoxel(v2);

        // call the copy constructor
        imgdata::Fracture fcpy(f);

        REQUIRE(fcpy.imgdata::Fracture::getVoxels() == 2);
        REQUIRE(fcpy.imgdata::Fracture::getID() == 1);
        REQUIRE(fcpy.imgdata::Fracture::getColour() == "blue");

        // Test that the coords vector of voxels initialises correctly
        auto testcoords = fcpy.imgdata::Fracture::getCoords();
        // test that the voxel at index 0 is correct
        REQUIRE(testcoords[0].imgdata::Voxel::getIntensity() == 155.0);
        REQUIRE(testcoords[0].imgdata::Voxel::getX() == 1);
        REQUIRE(testcoords[0].imgdata::Voxel::getY() == 2);
        REQUIRE(testcoords[0].imgdata::Voxel::getZ() == 3);
        // test that the voxel at index 1 is correct
        REQUIRE(testcoords[1].imgdata::Voxel::getIntensity() == 255.0);
        REQUIRE(testcoords[1].imgdata::Voxel::getX() == 4);
        REQUIRE(testcoords[1].imgdata::Voxel::getY() == 5);
        REQUIRE(testcoords[1].imgdata::Voxel::getZ() == 6);
    }
    
    SECTION("Copy Assignment Operator") {
        imgdata::Fracture f = imgdata::Fracture(1, (std::string)"blue");
        // populate the vector of coords with 2 Voxels
        imgdata::Voxel v1(1,2,3,155.0);
        imgdata::Voxel v2(4,5,6,255.0);
        f.imgdata::Fracture::insertVoxel(v1);
        f.imgdata::Fracture::insertVoxel(v2);

        // call the copy assignment operator
        imgdata::Fracture fcpy = f;
        
        REQUIRE(fcpy.imgdata::Fracture::getVoxels() == 2);
        REQUIRE(fcpy.imgdata::Fracture::getID() == 1);
        REQUIRE(fcpy.imgdata::Fracture::getColour() == "blue");

        // Test that the coords vector of voxels initialises correctly
        auto testcoords = fcpy.imgdata::Fracture::getCoords();
        // test that the voxel at index 0 is correct
        REQUIRE(testcoords[0].imgdata::Voxel::getIntensity() == 155.0);
        REQUIRE(testcoords[0].imgdata::Voxel::getX() == 1);
        REQUIRE(testcoords[0].imgdata::Voxel::getY() == 2);
        REQUIRE(testcoords[0].imgdata::Voxel::getZ() == 3);
        // test that the voxel at index 1 is correct
        REQUIRE(testcoords[1].imgdata::Voxel::getIntensity() == 255.0);
        REQUIRE(testcoords[1].imgdata::Voxel::getX() == 4);
        REQUIRE(testcoords[1].imgdata::Voxel::getY() == 5);
        REQUIRE(testcoords[1].imgdata::Voxel::getZ() == 6);
    }

    SECTION("Move Constructor") {
        imgdata::Fracture f = imgdata::Fracture(1, (std::string)"blue");
        // populate the vector of coords with 2 Voxels
        imgdata::Voxel v1(1,2,3,155.0);
        imgdata::Voxel v2(4,5,6,255.0);
        f.imgdata::Fracture::insertVoxel(v1);
        f.imgdata::Fracture::insertVoxel(v2);
        
        // call the move constructor
        imgdata::Fracture fmove(std::move(f));

        REQUIRE(fmove.imgdata::Fracture::getVoxels() == 2);
        REQUIRE(fmove.imgdata::Fracture::getID() == 1);
        REQUIRE(fmove.imgdata::Fracture::getColour() == "blue");

        // Test that the coords vector of voxels initialises correctly
        auto testcoords = fmove.imgdata::Fracture::getCoords();
        // test that the voxel at index 0 is correct
        REQUIRE(testcoords[0].imgdata::Voxel::getIntensity() == 155.0);
        REQUIRE(testcoords[0].imgdata::Voxel::getX() == 1);
        REQUIRE(testcoords[0].imgdata::Voxel::getY() == 2);
        REQUIRE(testcoords[0].imgdata::Voxel::getZ() == 3);
        // test that the voxel at index 1 is correct
        REQUIRE(testcoords[1].imgdata::Voxel::getIntensity() == 255.0);
        REQUIRE(testcoords[1].imgdata::Voxel::getX() == 4);
        REQUIRE(testcoords[1].imgdata::Voxel::getY() == 5);
        REQUIRE(testcoords[1].imgdata::Voxel::getZ() == 6);

        REQUIRE(f.imgdata::Fracture::getVoxels() == 0);
        REQUIRE(f.imgdata::Fracture::getID() == -1);
        REQUIRE(f.imgdata::Fracture::getColour() == "null");
         // Test that the coords vector of voxels has been cleared
        auto testorigcoords = f.imgdata::Fracture::getCoords();
        REQUIRE(testorigcoords.empty());
    }

    SECTION("Move Assignment Operator") {
        imgdata::Fracture f = imgdata::Fracture(1, (std::string)"blue");
        // populate the vector of coords with 2 Voxels
        imgdata::Voxel v1(1,2,3,155.0);
        imgdata::Voxel v2(4,5,6,255.0);
        f.imgdata::Fracture::insertVoxel(v1);
        f.imgdata::Fracture::insertVoxel(v2);
        
        // call the move assignment operator
        imgdata::Fracture fmove = std::move(f);

        REQUIRE(fmove.imgdata::Fracture::getVoxels() == 2);
        REQUIRE(fmove.imgdata::Fracture::getID() == 1);
        REQUIRE(fmove.imgdata::Fracture::getColour() == "blue");

        // Test that the coords vector of voxels initialises correctly
        auto testcoords = fmove.imgdata::Fracture::getCoords();
        // test that the voxel at index 0 is correct
        REQUIRE(testcoords[0].imgdata::Voxel::getIntensity() == 155.0);
        REQUIRE(testcoords[0].imgdata::Voxel::getX() == 1);
        REQUIRE(testcoords[0].imgdata::Voxel::getY() == 2);
        REQUIRE(testcoords[0].imgdata::Voxel::getZ() == 3);
        // test that the voxel at index 1 is correct
        REQUIRE(testcoords[1].imgdata::Voxel::getIntensity() == 255.0);
        REQUIRE(testcoords[1].imgdata::Voxel::getX() == 4);
        REQUIRE(testcoords[1].imgdata::Voxel::getY() == 5);
        REQUIRE(testcoords[1].imgdata::Voxel::getZ() == 6);

        REQUIRE(f.imgdata::Fracture::getVoxels() == 0);
        REQUIRE(f.imgdata::Fracture::getID() == -1);
        REQUIRE(f.imgdata::Fracture::getColour() == "null");
         // Test that the coords vector of voxels has been cleared
        auto testorigcoords = f.imgdata::Fracture::getCoords();
        REQUIRE(testorigcoords.empty());
    }

    SECTION("insertVoxel Member Function") {
        imgdata::Fracture f = imgdata::Fracture(1, (std::string)"blue");
        // populate the vector of coords with 1 Voxel
        imgdata::Voxel v1(1,2,3,155.0);
        // call the insertVoxel function
        f.imgdata::Fracture::insertVoxel(v1);
        // Test that voxel has been inserted correctly
        auto testcoords = f.imgdata::Fracture::getCoords();
        REQUIRE(testcoords[0].imgdata::Voxel::getIntensity() == 155.0);
        REQUIRE(testcoords[0].imgdata::Voxel::getX() == 1);
        REQUIRE(testcoords[0].imgdata::Voxel::getY() == 2);
        REQUIRE(testcoords[0].imgdata::Voxel::getZ() == 3);
    }
}

TEST_CASE ("imgread: CTReader class") {
    SECTION("readPGMStack Member Function") {
        // This checks that no seg faults take place during the read-in or de-allocation
        imgread::CTReader ctr;
	std::string fname("images/cross256_14/test-D256-V3086-F14-.hdr");
        auto testctr = ctr.imgread::CTReader::readPGMStack(fname);
    }
}


TEST_CASE("imgpro: Split Class")
{
	int dim = 3;
	imgdata::Voxel *** cube = new imgdata::Voxel ** [dim];
	for(int z = 0; z < dim; z++)
	{
		imgdata::Voxel ** layer = new imgdata::Voxel * [dim];
		for(int x = 0; x < dim; x++)
		{
			imgdata::Voxel * row = new imgdata::Voxel [dim];
			row[0] = imgdata::Voxel(x,0,z,0);
			row[1] = imgdata::Voxel(x,1,z,100);
			row[2] = imgdata::Voxel(x,2,z,200);
			layer[x] = row;
		}
		cube[z] = layer;
	}

	SECTION("Default Constructor")
	{
		imgpro::Split s;
		REQUIRE(s.getData() == nullptr);
		REQUIRE(s.getAllFrac() == false);
		REQUIRE(s.getSomeFrac() == true);
		REQUIRE(s.getDepth() == 0);
		REQUIRE(s.getRows() == 0);
		REQUIRE(s.getCols() == 0);
		REQUIRE(s.getID() == -1);
	}
	SECTION("Custom Constructor")
	{
		imgpro::Split s(cube, dim, dim, dim);

		REQUIRE(s.getData() == cube);
		REQUIRE(s.getAllFrac() == false);
		REQUIRE(s.getSomeFrac() == true);
		REQUIRE(s.getDepth() == dim);
		REQUIRE(s.getRows() == dim);
		REQUIRE(s.getCols() == dim);
		REQUIRE(s.getID() == -1);
	}
	SECTION("Copy Constructor")
	{
		imgpro::Split s1(cube, dim, dim, dim);
		imgpro::Split s2(s1);

		REQUIRE(s2.getData() != s1.getData());	
		REQUIRE(s2.getAllFrac() == s1.getAllFrac());
		REQUIRE(s2.getSomeFrac() == s1.getSomeFrac());
		REQUIRE(s2.getDepth() == s1.getDepth());
		REQUIRE(s2.getRows() == s1.getRows());
		REQUIRE(s2.getCols() == s1.getCols());
		REQUIRE(s2.getID() == s1.getID());
	}
	SECTION("Move Constructor")
	{
		imgpro::Split s2(imgpro::Split(cube,dim,dim,dim));


		REQUIRE(s2.getAllFrac() == false);
		REQUIRE(s2.getSomeFrac() == true);
		REQUIRE(s2.getDepth() == dim);
		REQUIRE(s2.getRows() == dim);
		REQUIRE(s2.getCols() == dim);
		REQUIRE(s2.getID() == -1);
	}
	SECTION("Copy Assignment Operator")
	{
		imgpro::Split s1(cube, dim, dim, dim);
		imgpro::Split s2 = s1;

		REQUIRE(s2.getData() != s1.getData());	
		REQUIRE(s2.getAllFrac() == s1.getAllFrac());
		REQUIRE(s2.getSomeFrac() == s1.getSomeFrac());
		REQUIRE(s2.getDepth() == s1.getDepth());
		REQUIRE(s2.getRows() == s1.getRows());
		REQUIRE(s2.getCols() == s1.getCols());
		REQUIRE(s2.getID() == s1.getID());
	}
	SECTION("Move Assignment Operator")
	{
		imgpro::Split s2 = imgpro::Split(cube, dim, dim, dim);
	
		REQUIRE(s2.getAllFrac() == false);
		REQUIRE(s2.getSomeFrac() == true);
		REQUIRE(s2.getDepth() == dim);
		REQUIRE(s2.getRows() == dim);
		REQUIRE(s2.getCols() == dim);
		REQUIRE(s2.getID() == -1);
	}
}
