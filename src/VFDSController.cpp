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

void VFDSController::loadFractures(std::string folderpath)
{
    fractures = func::loadGroupFractures(folderpath);
}

void VFDSController::saveFractures(std::string folderpath)
{
    char* c = const_cast<char*>(folderpath.c_str());
    func::saveGroupFractures(fractures,c,depth);
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
    detectEnable=true;

    emit dataRead(readDataSuccess);
}

void VFDSController::applyThreshold()
{
    thresholdImageData = new unsigned char ** [depth];
    for(int j = 0; j < depth; ++j) {
        thresholdImageData[j] = new unsigned char * [depth];
        for (int k = 0; k < depth; ++k) {
            thresholdImageData[j][k] = new unsigned char [depth];
        }
    }

    denoise::AdaptiveThreshold at(depth, 3, sigma_s, sigma_m);

    for(int i =0; i<depth; ++i)
    {
        at.execute(imageData,thresholdImageData,i);
    }


}

void VFDSController::detectFractures()
{
    if(readDataSuccess)
    {
        
    }
}

void VFDSController::charToVoxel(bool at)
{

    if(readDataSuccess && detectEnable && at)
    {
        vimgData = func::toVoxels(thresholdImageData,depth);
        voxelDataLoaded=true;
        emit updateStatus("1/3: Raw data parsed...");
    }
    else
    {
        vimgData = func::toVoxels(imageData,depth);
        voxelDataLoaded=true;
        emit updateStatus("1/3: Raw data parsed...");
    }

}

void VFDSController::fillBackground()
{
    if(readDataSuccess && voxelDataLoaded)
    {
        func::paintBackground(vimgData,depth,depth,depth,150);
        backgroundFilled = true;
        emit updateStatus("2/3: Background painted...");
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
