/*
Jared May
25/09/2021
VFDS Main Window
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtGui>
//#include <Qt>

#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QScrollArea>
#include <QFileDialog>
#include <QStatusBar>

#include <QLineEdit>
#include <QMessageBox>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "VFDSController.h"
#include "ImageProcessor.h"
#include "CTReader.h"
#include "detectiondialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        bool loadFile(const QString &);

        imgread::CTReader *ctReader;
        //std::string files = "";
        //std::string shape = "";
        //int dim = 0;

    private slots:
        void open();
        //void saveAs();
        //void load();
        //void print();
        //void copy();
        //void paste();
        //void zoomIn();
        //void zoomOut();
        //void normalSize();
        //void fitToWindow();
        void about();
        void next();
        void back();
        void detectFractures();
        void detectionDialogShow();

    public slots:

    signals:
        


    private: 
        
        DetectionDialog detectionDialog;
        const QString fractureLabelText = "Layer: ";
        const QString nFracturesLabelText = "Fractures detected: ";
        void displayImage();
        VFDSController *vfdsController;

        //Init Methods
        void setupSignalsAndSlots();
        void setupCoreWidgets();
        void createMenus();
        void setupLayout();

        /*
        void createActions();
        void createMenus();
        void updateActions();
        bool saveFile(const QString &fileName);
        void setImage(const QImage &newImage);
        void scaleImage(double factor);
        void adjustScrollBar(QScrollBar *scrollBar, double factor);
        */

        //Display
        QImage image;
        QScrollArea *scrollArea;
        double scaleFactor = 1;

        // Layout and Widgets

        QWidget *mainWidget;
        QWidget *infoWidget;
        QHBoxLayout *centralWidgetLayout;
        QVBoxLayout *sidePanelLayout;
        QGridLayout *viewLayout;
        QHBoxLayout *sidePanelButtonsLayout;

        // Menus
        QMenu *fileMenu;
        QMenu *helpMenu;
        QMenu *toolsMenu;
        //QMenu *detectionMenu;

        // Actions
        QAction *quitAction;
        QAction *aboutAction;
        QAction *openAction;
        QAction *nextAction;
        QAction *backAction;
        QAction *detectFracturesAction;
        QAction *detectionPreferences;
        //QAction *cancelAction;
        //QAction *newAction;
        //QAction *saveAsAct;
        //QAction *printAct;
        //QAction *loadAction;
        //QAction *copyAct;
        //QAction *zoomInAction;
        //QAction *zoomOutAction;
        //QAction *normalSizeAction;
        //QAction *fitToWindowAction;

        //Labels
        QLabel *imageLabel;
        QLabel *nFracturesLabel;
        QLabel *fractureLabel;
        QLabel *partLabel;

        //Buttons
        QPushButton *nextPushButton;
        QPushButton *backPushButton;
        QPushButton *detectFracturesPushButton;

        //Input
        QLineEdit *fileLineEdit;
        QFileDialog *fileDialog;
};
#endif // MAINWINDOW_H
