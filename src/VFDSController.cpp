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

VFDSController::VFDSController(QObject *parent)
{
    setParent(parent);
    //connect(parent,)
    //connect(&parent,)
}

VFDSController::VFDSController(std::string &hdrFilePath){
    headerFilePath = hdrFilePath;
    //setParent(parent);
    //connect(this, &VFDSController::dataRead,this,&MainWindow::dataLoaded);
}

VFDSController::~VFDSController(){
}

void VFDSController::loadFractures()
{
   //fractures = func::loadGroupFractures()
}

void VFDSController::readData(std::string hdrFilePath)
{
    headerFilePath=hdrFilePath;
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

void VFDSController::colourFractures()
{
    int cc(0);
    //func::writeCubeColour()
    for (std::vector<imgdata::Fracture>::iterator i = fractures.begin(); i!=fractures.end(); ++i) {
        if(cc%5 == 0)
        {
            i->setColour("white");
        }
        else if(cc%5 == 1)
        {
            i->setColour("red");
        }
        else if(cc%5 == 2)
        {
            i->setColour("green");
        }
        else if(cc%5 == 3)
        {
            i->setColour("blue");
        }
        else if( cc%5 == 4)
        {
            i->setColour("yellow");
        }
        cc++;
    }

    colourImageData = func::preparePPMCube(imageData,depth,fractures);

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
