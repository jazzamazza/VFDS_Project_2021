// unit testing file for the imgdata and imgread namespaces for the VFDS
// htciai001
// 26/08/21

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CTReader.h"
#include "BackgroundData.h"
#include "PartData.h"
#include "Voxel.h"
#include "Fracture.h"

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
