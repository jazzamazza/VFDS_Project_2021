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

std::size_t VFDSController::getNFractures() const
{
    return nFractures;
}

VFDSController::VFDSController(std::string &hdrFilePath, QObject *parent){
    headerFilePath = hdrFilePath;
     //connect(this, &VFDSController::dataRead,this,&MainWindow::dataLoaded);
}

VFDSController::~VFDSController(){
}

void VFDSController::readData()
{
    imageData=ctReader.readPGMStack(headerFilePath);
    //std::cout << (sizeof(unsigned char)*256*256*265)/1024/1024<<" megabytes is size of imgdata"<<std::endl;
    //std::cout << (sizeof(imgdata::Voxel)*256*256*265)/1024/1024<<" megabytes is size of voxel rep of imgdata"<<std::endl;
    //std::cout << sizeof(int)*3<<" bytes is 3 int"<<std::endl;
    //std::cout << sizeof(std::vector<int>)*3<<" bytes is 3 vector of int"<<std::endl;

    readDataSuccess=true;
    imageN = 0;
    depth = ctReader.getDim();
    dataFolderPath = ctReader.getDir();
    pgmPath = ctReader.getPGM(headerFilePath,imageN);

    emit dataRead(readDataSuccess);
}

void VFDSController::detectFractures()
{
    if(readDataSuccess)
    {
        
    }
}

void VFDSController::charToVoxel()
{
    if(readDataSuccess)
    {
        vimgData = func::toVoxels(imageData,depth);
        voxelDataLoaded=true;
    }
       
}

void VFDSController::fillBackground()
{
    if(readDataSuccess && voxelDataLoaded)
    {
        func::paintBackground(vimgData,depth,depth,depth,150);
        backgroundFilled = true;
    }
}

void VFDSController::runSplitMerge()
{
    if(readDataSuccess && voxelDataLoaded && backgroundFilled){
        fractures = func::splitMerge(vimgData,depth,depth,depth);
        splitMergeSuccess=true;
        nFractures = fractures.size();
    }
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
