/*
Jared May
25/09/2021
VFDS Main Window
*/
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Volumetric Fracture Detection System");

    //setSizePolicy(QSizePoli)

    //setFixedSize(750,600);
    setMinimumSize(750,600);
    statusBar()->showMessage("Ready...");

    setupCoreWidgets();
    setupLayout();
    createMenus();

    setCentralWidget(mainWidget);

    setupSignalsAndSlots();
    //std::cout << "width: " << imageLabel->size().width() << " height: "<< imageLabel->size().height();
}

MainWindow::~MainWindow()
{
}



void MainWindow::setupCoreWidgets(){
    //Setup Widgets and Layout

    mainWidget = new QWidget();
    infoWidget = new QWidget();

    centralWidgetLayout = new QHBoxLayout();
    viewLayout = new QGridLayout();
    sidePanelLayout = new QVBoxLayout();
    sidePanelButtonsLayout = new QHBoxLayout();

    //sidePanelLayout

    //Setup labels
    imageLabel = new QLabel();
    imageLabel -> setMinimumSize(600,600);
    //imageLabel -> setFixedSize(500,500);
    imageLabel -> setBackgroundRole(QPalette::Base);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel -> setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    imageLabel -> setScaledContents(true);
//todo
    scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setAlignment(Qt::AlignCenter);
    //scrollArea->setVisible(false);
    scrollArea->setFrameShape(QFrame::StyledPanel);

    //Setup buttons
    //loadPushButton = new QPushButton("Load");
    nextPushButton = new QPushButton("Next");
    backPushButton = new QPushButton("Back");
    detectFracturesPushButton = new QPushButton("Detect fractures");

    //Setup input
    fileLineEdit = new QLineEdit();

    //Layout
    viewLayout->addWidget(scrollArea, 0, 0);
    viewLayout->setColumnMinimumWidth(0,505);
    viewLayout->setRowMinimumHeight(0,505);
    //viewLayout->addWidget(imageLabel,1,0);
    //formLayout->addWidget(fileLineEdit,0,1);
    //gridLayout->addWidget(imageLabel,1,0);

    sidePanelLayout->addWidget(nFracturesLabel = new QLabel(nFracturesLabelText + "unknown"));
    //nFracturesLabel->setText("Fractures detected: ");

    sidePanelLayout->addWidget(fractureLabel = new QLabel(fractureLabelText));
    //fractureLabel->setText("Fracture");
    //fractureLabel->setText("Layer: ");
    sidePanelLayout->addStretch();
    sidePanelLayout->addWidget(detectFracturesPushButton);


    //sidePanelButtonsLayout->addStretch();
    sidePanelButtonsLayout->addWidget(nextPushButton);
    sidePanelButtonsLayout->addWidget(backPushButton);

    nextPushButton->setEnabled(false);
    backPushButton->setEnabled(false);
    
}

void MainWindow::setupLayout(){
    centralWidgetLayout->addLayout(viewLayout);
    //centralWidgetLayout->addWidget(mainWidget);
    sidePanelLayout->addLayout(sidePanelButtonsLayout);
    //centralWidgetLayout->addLayout(buttonsLayout);
    centralWidgetLayout->addLayout(sidePanelLayout);
    mainWidget->setLayout(centralWidgetLayout);
}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu("&File");

    //displayMenu = menuBar()->addMenu("Display");
    //detectionMenu = menuBar()->addMenu("Detection");
    toolsMenu = menuBar()->addMenu("&Tools");

    detectionPreferences = new QAction("&Detection Parameters",this);
    toolsMenu->addAction(detectionPreferences);
    
    //newAction = new QAction("&New", this);
    //newAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    openAction = new QAction("&Open", this);
    openAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    fileMenu->addAction(openAction);



    
    fileMenu->addSeparator();
    quitAction = new QAction("Quit", this);
    quitAction->setShortcuts(QKeySequence::Quit);
    fileMenu->addAction(quitAction);

    helpMenu = menuBar()->addMenu("Help");
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

    //detectFracturesAction = new QAction();
    //detectFracturesPushButton->addAction(detectFracturesAction);

    connect(quitAction, &QAction::triggered, this, &QApplication::quit);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    connect(nextPushButton,SIGNAL(clicked()),this,SLOT(next()));
    connect(nextAction, &QAction::triggered, this, &MainWindow::next);

    connect(backPushButton,SIGNAL(clicked()),this,SLOT(back()));
    connect(backAction, &QAction::triggered, this, &MainWindow::back);

    connect(detectFracturesPushButton,SIGNAL(clicked()),this,SLOT(detectFractures()));

    connect(detectionPreferences, &QAction::triggered, this, &MainWindow::detectionDialogShow);

    //connect(detectionPreferences, &QAction::triggered,DetectionDialog(this),detectionDialog.show());
}


void MainWindow::open(){
    //detectionDialog.show();
    fileDialog = new QFileDialog();

    //Get path to hdr file from fileDialog
    QString filename = fileDialog->getOpenFileName(this,tr("Choose"),"", tr("Header File (*.hdr)"));

    if (QString::compare(filename,QString())!=0)//no file selected i.e. cancel clicked
    {
        std::string hdrFilePath = filename.toStdString();

        //create new VFDSController for file
        vfdsController = new VFDSController(hdrFilePath);

        //Load data set
        vfdsController->readData();

        //if ct reader successfully reads data
        MainWindow::displayImage();
        statusBar()->showMessage("Image loaded...");

        backPushButton->setEnabled(false);
        nextPushButton->setEnabled(true);
        nextAction->setEnabled(true);
        backAction->setEnabled(true);

        fractureLabel->setText(fractureLabelText+QString::number(vfdsController->getImageN()+1)+"/"+QString::number(vfdsController->getDepth()));
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
    vfdsController->incImageN();
    MainWindow::displayImage();
    //fractureLabel->setText(fractureLabelText+QString::number(vfdsController->getImageN()));
    fractureLabel->setText(fractureLabelText+QString::number(vfdsController->getImageN()+1)+"/"+QString::number(vfdsController->getDepth()));

    if (vfdsController->getImageN()==vfdsController->getDepth()-1)
    {
        nextPushButton->setEnabled(false);
        nextAction->setEnabled(false);
    }

    if (vfdsController->getImageN() > 0)
    {
        backPushButton->setEnabled(true);
        backAction->setEnabled(true);
    }
}

void MainWindow::back()
{
    vfdsController->decImageN();
    MainWindow::displayImage();
    //fractureLabel->setText(fractureLabelText+QString::number(vfdsController->getImageN()));
    fractureLabel->setText(fractureLabelText+QString::number(vfdsController->getImageN()+1)+"/"+QString::number(vfdsController->getDepth()));

    if (vfdsController->getImageN() == 0)
    {
        backPushButton->setEnabled(false);
        backAction->setEnabled(false);
    }

    if (vfdsController->getImageN() < vfdsController->getDepth()-1)
    {
        nextPushButton->setEnabled(true);
        nextAction->setEnabled(true);
    }

}

void MainWindow::detectFractures()
{
    statusBar()->showMessage("Fracture detection started...");
    vfdsController->charToVoxel();
    if (vfdsController->voxelDataLoaded)
    {
        statusBar()->showMessage("1/3: Raw data parsed...");
        vfdsController->fillBackground();
        if (vfdsController->backgroundFilled)
        {
            statusBar()->showMessage("2/3: Background data processed...");
            vfdsController->runSplitMerge();
            if (vfdsController->splitMergeSuccess)
            {
                statusBar()->showMessage("3/3: Fractures detected...");
                nFracturesLabel->setText(nFracturesLabelText+QString::number(vfdsController->getNFractures()));
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
    if(vfdsController->getReadDataSuccess()){

        std::string pgmFilePath = vfdsController->getPgmPath();

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
