#ifndef VFDSCONTROLLER_H
#define VFDSCONTROLLER_H

#include "ImageProcessor.h"
#include "Split.h"
#include "Voxel.h"
#include "Fracture.h"
#include "CTReader.h"
#include "Filter.h"

#include <string>
#include <vector>

#include <iostream>

#include <QObject>

class VFDSController : public QObject
{
    Q_OBJECT

public slots:
    

signals:
    void dataRead(bool read);
   

private:
    /* data */

    imgread::CTReader ctReader;
    imgdata::Voxel*** vimgData;

    std::string headerFilePath; //PGM Dataset .hdr file path
    std::string dataFolderPath; //PGM Dataset folder path

    std::string fractureFolderPath; //Fracture data input folder path
    std::string outputFolderPath; //Fracture data output folder path

    std::vector<imgdata::Fracture> fractures; //Vector of Fractures

    unsigned char*** imageData; //Raw Array of pixel data
    int depth = 0; //Dimensions of image stack
    int imageN = 0;
    std::size_t nFractures = 0;
    std::string pgmPath;

    //filters to do
    imgfltr::BilateralFilter<unsigned char> bf; //Bilateral filter

    //adaptive threshold stuff to do

    enum traversalAxis {x,y,z} axis; //axis of traversal
    enum denoiseAlg{Median, Bilateral} denoise; //to do    

public:
    VFDSController(std::string &hdrFilePath, QObject *parent);
    ~VFDSController();


    void readData();
    void detectFractures();

    std::string getHeaderFilePath();
    void setHeaderFilePath(const std::string &newHeaderFilePath);

    std::string getDataFolderPath();
    void setDataFolderPath(const std::string &newDataFolderPath);
    void setDataFolderPath();

    int getImageN() const;
    void setImageN(int newImageN);
    bool getReadDataSuccess() const;
    const std::string &getPgmPath();
    void setPgmPath();

    void incImageN();
    void decImageN();
    int getDepth() const;
    std::size_t getNFractures() const;

    void charToVoxel();
    void fillBackground();
    void runSplitMerge();

    bool splitMergeSuccess=false;
    bool saveEnable=false;
    bool loadEnable=false;
    bool detectEnable=false;
    bool renderingOn=false;
    bool voxelDataLoaded=false;
    bool backgroundFilled =false;
    bool newDataSet=true;
    bool readDataSuccess=false;

};

#endif
