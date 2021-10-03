/*
Jared May
25/09/2021
VFDS Main
*/
#include <QApplication>
#include "mainwindow.h"

#include "Split.h"
#include "Voxel.h"
#include "ImageProcessor.h"
#include "Fracture.h"
#include "CTReader.h"

int main(int argc, char *argv[])
{
    using namespace imgdata;

    imgread::CTReader ctReader;
    std::string files = "";
    std::string shape = "";
    int dim = 0;
    QApplication app(argc, argv);
    //QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar); //fix for menubar notshowing in ubuntu

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}