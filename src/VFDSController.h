#ifndef VFDSCONTROLLER_H
#define VFDSCONTROLLER_H

#include "ImageProcessor.h"
#include "Split.h"
#include "Voxel.h"
#include "Fracture.h"
#include "CTReader.h"
#include "Filter.h"
//#include "mainwindow.h"
#include "AdaptiveThreshold.h"

#include <string>
#include <vector>

#include <iostream>

#include <QObject>
#include <QWidget>

class VFDSController : public QObject
{
    Q_OBJECT

public slots:
    void colourFractures();


signals:
    void dataRead(bool read);
    void updateStatus(std::string status);

   

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
    unsigned char*** colourImageData;
    unsigned char*** thresholdImageData;


    int depth = 0; //Dimensions of image stack
    int imageN = 0;

    double sigma_s = 0.0;
    double sigma_m = 0.0;
    std::size_t nFractures = 0;
    std::string pgmPath;

    //filters to do
    imgfltr::BilateralFilter<unsigned char> bf; //Bilateral filter

    //adaptive threshold stuff to do

    enum traversalAxis {x,y,z} axis; //axis of traversal
    enum denoiseAlg{Median, Bilateral} denoise; //to do    

public:
    VFDSController(QObject *parent=nullptr);
    VFDSController(std::string &hdrFilePath);
    ~VFDSController();

    void loadFractures(std::string folderpath);
    void saveFractures(std::string folderpath);

    void readData(std::string hdrFilePath);
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
    void charToVoxel(unsigned char*** atData);



    bool splitMergeSuccess=false;
    bool saveEnable=false;
    bool loadEnable=false;
    bool detectEnable=false;
    bool atEnable=false;
    bool renderingOn=false;
    bool voxelDataLoaded=false;
    bool backgroundFilled =false;
    bool newDataSet=true;
    bool readDataSuccess=false;

    void applyThreshold();
};

#endif
