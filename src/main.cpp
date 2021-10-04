/*
Jared May
25/09/2021
VFDS Main
*/
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar); //fix for menubar notshowing in ubuntu

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
