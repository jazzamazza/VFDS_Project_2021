/*
Jared May
25/09/2021
VFDS Main Window
*/
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //set window properties
    setWindowTitle("Volumetric Fracture Detection System");
    setMinimumSize(750,600);
    statusBar()->showMessage("Ready...");

    //setup window
    setupCoreWidgets();
    setupLayout();
    createMenus();
    setCentralWidget(mainWidget);

    //setup event handling
    setupSignalsAndSlots();
}

MainWindow::~MainWindow()
{
}


void MainWindow::setupCoreWidgets(){
    //Setup Widgets
    mainWidget = new QWidget();
    infoWidget = new QWidget();

    //Setup buttons
    nextPushButton = new QPushButton("Next");
    backPushButton = new QPushButton("Back");
    detectFracturesPushButton = new QPushButton("Detect fractures");
    nextPushButton->setEnabled(false);
    backPushButton->setEnabled(false);
    detectFracturesPushButton->setEnabled(false);

    //Setup input
    fileDialog = new QFileDialog();

    //Setup labels and display
    imageLabel = new QLabel();
    imageLabel -> setMinimumSize(550,550);
    imageLabel -> setBackgroundRole(QPalette::Base);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel -> setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    imageLabel -> setScaledContents(true);

    statisticsLabel = new QLabel("Statistics");
    QFont statFont = statisticsLabel->font();
    statFont.setWeight(QFont::Bold);
    statFont.setUnderline(true);
    statisticsLabel->setFont(statFont);
    statisticsLabel->setAlignment(Qt::AlignCenter);
    nFracturesLabel = new QLabel(nFracturesLabelText + "unknown");
    fractureLabel = new QLabel(fractureLabelText);
    
    scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setAlignment(Qt::AlignCenter);
    //scrollArea->setVisible(false);
    scrollArea->setFrameShape(QFrame::StyledPanel);    
}

void MainWindow::setupLayout(){

    centralWidgetLayout = new QHBoxLayout();
    viewLayout = new QGridLayout();
    sidePanelLayout = new QVBoxLayout();
    sidePanelButtonsLayout = new QHBoxLayout();

    //Layout layouts
    centralWidgetLayout->addLayout(viewLayout);
    //centralWidgetLayout->addWidget(infoWidget);
    centralWidgetLayout->addLayout(sidePanelLayout);


    //Set up view layout
    viewLayout->addWidget(scrollArea, 0, 0);
    viewLayout->setColumnMinimumWidth(0,600);
    viewLayout->setRowMinimumHeight(0,600);

    //set up sidepanel layout
    //sidePanelLayout->addStretch();
    sidePanelLayout->addWidget(statisticsLabel);
    sidePanelLayout->addWidget(nFracturesLabel);
    sidePanelLayout->addWidget(fractureLabel);
    sidePanelLayout->addStretch();
    sidePanelLayout->addWidget(detectFracturesPushButton);
    sidePanelLayout->addLayout(sidePanelButtonsLayout);
    sidePanelButtonsLayout->addWidget(nextPushButton);
    sidePanelButtonsLayout->addWidget(backPushButton);

    mainWidget->setLayout(centralWidgetLayout);

}

void MainWindow::createMenus(){
    
    fileMenu = menuBar()->addMenu("&File");

    openAction = new QAction("&Open", this);
    openAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    quitAction = new QAction("Quit", this);
    quitAction->setShortcuts(QKeySequence::Quit);
    fileMenu->addAction(quitAction);

    toolsMenu = menuBar()->addMenu("&Tools");

    detectionPreferences = new QAction("&Detection Parameters",this);
    toolsMenu->addAction(detectionPreferences);

    helpMenu = menuBar()->addMenu("&Help");

    aboutAction = new QAction("About", this);
    aboutAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_H));
    helpMenu->addAction(aboutAction);

}

void MainWindow::setupSignalsAndSlots() {
    // Setup Signals and Slots
    nextAction = new QAction();
    nextAction -> setShortcut(QKeySequence(Qt::Key_Right));
    nextPushButton->addAction(nextAction);
    nextAction->setEnabled(false);

    backAction = new QAction();
    backAction -> setShortcut(QKeySequence(Qt::Key_Left));
    backPushButton->addAction(backAction);
    backAction->setEnabled(false);

    connect(quitAction, &QAction::triggered, this, &QApplication::quit);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    connect(nextPushButton,SIGNAL(clicked()),this,SLOT(next()));
    connect(nextAction, &QAction::triggered, this, &MainWindow::next);

    connect(backPushButton,SIGNAL(clicked()),this,SLOT(back()));
    connect(backAction, &QAction::triggered, this, &MainWindow::back);

    connect(detectFracturesPushButton,SIGNAL(clicked()),this,SLOT(detectFractures()));

    connect(detectionPreferences, &QAction::triggered, this, &MainWindow::detectionDialogShow);

    connect(&vfdsController,&VFDSController::dataRead,this,&MainWindow::dataLoaded);

    //connect(vfdsController, &VFDSController::dataRead,this,&MainWindow::dataLoaded);

    
}

void MainWindow::dataLoaded(bool bRead)
{
        detectFracturesPushButton->setEnabled(bRead);
    
}

void MainWindow::open(){
    //Get path to hdr file from fileDialog
    QString filename = fileDialog->getOpenFileName(this,tr("Choose"),"", tr("Header File (*.hdr)"));

    if (QString::compare(filename,QString())!=0)//no file selected i.e. cancel clicked
    {
        std::string hdrFilePath = filename.toStdString();

        //create new VFDSController for file
        //vfdsController = new VFDSController(hdrFilePath);

        //Load data set
        vfdsController.readData(hdrFilePath);

        //if ct reader successfully reads data
        MainWindow::displayImage();
        statusBar()->showMessage("Image loaded...");

        backPushButton->setEnabled(false);
        nextPushButton->setEnabled(true);
        nextAction->setEnabled(true);
        backAction->setEnabled(true);

        fractureLabel->setText(fractureLabelText+QString::number(vfdsController.getImageN()+1)+"/"+QString::number(vfdsController.getDepth()));
    }
    else
    QMessageBox::warning(this,"No file selected","Please select a file",QMessageBox::Ok,QMessageBox::Default);

}

void MainWindow::about()
{

    QMessageBox::about(this, "About VFDS System",
                        "Volumetric Fracture Detection System"
                        "<p>"
                        "This is a simple application to display PGM files");
}

void MainWindow::next()
{
    vfdsController.incImageN();
    MainWindow::displayImage();
    //fractureLabel->setText(fractureLabelText+QString::number(vfdsController.getImageN()));
    fractureLabel->setText(fractureLabelText+QString::number(vfdsController.getImageN()+1)+"/"+QString::number(vfdsController.getDepth()));

    if (vfdsController.getImageN()==vfdsController.getDepth()-1)
    {
        nextPushButton->setEnabled(false);
        nextAction->setEnabled(false);
    }

    if (vfdsController.getImageN() > 0)
    {
        backPushButton->setEnabled(true);
        backAction->setEnabled(true);
    }
}

void MainWindow::back()
{
    vfdsController.decImageN();
    MainWindow::displayImage();
    //fractureLabel->setText(fractureLabelText+QString::number(vfdsController.getImageN()));
    fractureLabel->setText(fractureLabelText+QString::number(vfdsController.getImageN()+1)+"/"+QString::number(vfdsController.getDepth()));

    if (vfdsController.getImageN() == 0)
    {
        backPushButton->setEnabled(false);
        backAction->setEnabled(false);
    }

    if (vfdsController.getImageN() < vfdsController.getDepth()-1)
    {
        nextPushButton->setEnabled(true);
        nextAction->setEnabled(true);
    }

}

void MainWindow::detectFractures()
{
    statusBar()->clearMessage();
    statusBar()->showMessage("Fracture detection started...");
    
    vfdsController.charToVoxel();
    if (vfdsController.voxelDataLoaded)
    {
        std::cout<<"load"<<std::endl;
        statusBar()->clearMessage();
        statusBar()->showMessage("1/3: Raw data parsed...");
        vfdsController.fillBackground();
        if (vfdsController.backgroundFilled)
        {
            std::cout<<"load"<<std::endl;
            statusBar()->clearMessage();
            statusBar()->showMessage("2/3: Background data processed...");
            vfdsController.runSplitMerge();
            if (vfdsController.splitMergeSuccess)
            {
                std::cout<<"load"<<std::endl;
                statusBar()->clearMessage();
                statusBar()->showMessage("3/3: Fractures detected...");
                nFracturesLabel->setText(nFracturesLabelText+QString::number(vfdsController.getNFractures()));
            }
        }
    }
    
    
    

}

void MainWindow::detectionDialogShow()
{
    detectionDialog.show();
}

void MainWindow::displayImage()
{
    //if ct reader successfully reads data
    if(vfdsController.getReadDataSuccess()){

        std::string pgmFilePath = vfdsController.getPgmPath();

        QString imgfile = QString::fromStdString(pgmFilePath);

        if (pgmFilePath.compare("")!=0)
        {
            QImage image;
            bool valid = image.load(imgfile);
            //bool valid = true;
            if(valid)
            {
               imageLabel->setPixmap(QPixmap::fromImage(image));
              // scrollArea->setVisible(true);
               
            }
            else
            {
                QMessageBox::warning(this,"Invalid file","Please select a valid PGM file",QMessageBox::Ok,QMessageBox::Default);
            }
        }
        else
        {
            QMessageBox::warning(this,"Invalid file path","Invalid file path",QMessageBox::Ok,QMessageBox::Default);
        }
    }
}
