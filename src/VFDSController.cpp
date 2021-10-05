#include "VFDSController.h"

int VFDSController::getImageN() const
{
    return imageN;
}

void VFDSController::setImageN(int newImageN)
{
    imageN = newImageN;
}

bool VFDSController::getReadDataSuccess() const
{
    return readDataSuccess;
}

const std::string &VFDSController::getPgmPath()
{
    VFDSController::setPgmPath();
    return pgmPath;
}

void VFDSController::setPgmPath()
{
    pgmPath=ctReader.getPGM(headerFilePath,imageN);
}

void VFDSController::incImageN()
{
    if(imageN<depth-1){
       imageN++;
    }
}

void VFDSController::decImageN()
{
    if(imageN>0){
       imageN--;
    }
}

int VFDSController::getDepth() const
{
    return depth;
}

VFDSController::VFDSController(std::string &hdrFilePath){
    headerFilePath = hdrFilePath;
}

VFDSController::~VFDSController(){
}

void VFDSController::readData()
{
    imageData=ctReader.readPGMStack(headerFilePath);

    readDataSuccess=true;
    imageN = 0;
    depth = ctReader.getDim();
    dataFolderPath = ctReader.getDir();
    pgmPath=ctReader.getPGM(headerFilePath,imageN);

    //func::splitMerge()
}

std::string VFDSController::getHeaderFilePath()
{
    return headerFilePath;
}

void VFDSController::setHeaderFilePath(const std::string &newHeaderFilePath)
{
    headerFilePath = newHeaderFilePath;
    //readDataSuccess = false;
    //etc.
}

std::string VFDSController::getDataFolderPath()
{
    return dataFolderPath;
}

void VFDSController::setDataFolderPath(const std::string &newDataFolderPath)
{
    dataFolderPath = newDataFolderPath;
}

void VFDSController::setDataFolderPath()
{
    dataFolderPath = ctReader.getDir(headerFilePath);
}
