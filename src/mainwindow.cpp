/*
Jared May
25/09/2021
VFDS Main Window
*/
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("VFDS App");

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

void MainWindow::setupLayout(){
    centralWidgetLayout->addLayout(viewLayout);
    //centralWidgetLayout->addWidget(mainWidget);
    sidePanelLayout->addLayout(sidePanelButtonsLayout);
    //centralWidgetLayout->addLayout(buttonsLayout);
    centralWidgetLayout->addLayout(sidePanelLayout);
    mainWidget->setLayout(centralWidgetLayout);
}

void MainWindow::setupCoreWidgets(){
    //Setup Widgets and Layout

    mainWidget = new QWidget();
    centralWidgetLayout = new QHBoxLayout();
    viewLayout = new QGridLayout();
    sidePanelLayout = new QVBoxLayout();
    sidePanelButtonsLayout = new QHBoxLayout();

    //Setup labels
    imageLabel = new QLabel();
    //imageLabel -> setMinimumSize(500,500);
    imageLabel -> setFixedSize(500,500);
    imageLabel -> setBackgroundRole(QPalette::Base);
    //imageLabel -> setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel -> setScaledContents(true);
//todo
    /*scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);*/

    //Setup buttons
    //loadPushButton = new QPushButton("Load");
    nextPushButton = new QPushButton("Next");
    backPushButton = new QPushButton("Back");

    //Setup input
    fileLineEdit = new QLineEdit();

    //Layout
    viewLayout->addWidget(imageLabel, 0, 0);
    viewLayout->setColumnMinimumWidth(0,505);
    viewLayout->setRowMinimumHeight(0,505);
    //viewLayout->addWidget(imageLabel,1,0);
    //formLayout->addWidget(fileLineEdit,0,1);
    //gridLayout->addWidget(imageLabel,1,0);

    sidePanelButtonsLayout->addStretch();
    sidePanelButtonsLayout->addWidget(nextPushButton);
    sidePanelButtonsLayout->addWidget(backPushButton);
    
}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu("&File");
    
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
    connect(quitAction, &QAction::triggered, this, &QApplication::quit);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    connect(openAction, &QAction::triggered, this, &MainWindow::open);
    connect(nextPushButton,SIGNAL(clicked()),this,SLOT(about()));
}
void MainWindow::open(){
    fileDialog = new QFileDialog();

    //fileDialog -> setFileMode(QFileDialog::Directory);
    //fileDialog -> setOption(QFileDialog::ShowDirsOnly, true);
    //QString directory = fileDialog->getExistingDirectory(this,"choose","",QFileDialog::ShowDirsOnly);
    //QString filename = fileDialog->getOpenFileName();

    QString filename = fileDialog->getOpenFileName(this,tr("Choose"),"", tr("Header File (*.hdr *.pgm)"));
    std::string filePath = filename.toStdString();
    //QMessageBox::information(this,filename,filename+"ctrreader start",QMessageBox::Ok,QMessageBox::NoButton);
    //unsigned char *** voxArr = ctReader->readPGMStack(filePath);
    //QMessageBox::information(this,filename,"ctrreader end",QMessageBox::Ok,QMessageBox::NoButton);

    if (QString::compare(filename, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(filename);
        //bool valid = true;
        if(valid)
        {
           imageLabel->setPixmap(QPixmap::fromImage(image));
           statusBar()->showMessage(filename);
        }
        else
        {
            QMessageBox::warning(this,"Invalid file selected","Please select a PGM file",QMessageBox::Ok,QMessageBox::Default);
        }
    }
    else
    {
        QMessageBox::warning(this,"No file selected","Please select a PGM file",QMessageBox::Ok,QMessageBox::Default);
    }
}

void MainWindow::about()
{

    QMessageBox::about(this, "About VFDS System",
                        "Volumetric Fracture Detection System"
                        "<p>"
                        "This is a simple application to display PGM files");
}

//find image dimension from folder name
int MainWindow::parseDim(std::string str)
{
    int dim = 0;
    std::string tmp = "";
    for (size_t i = 0; i < str.length(); i++)
    {
        if (std::isdigit(str[i]))
        {
            tmp.push_back(str[i]);
        }
    }
    dim = std::stoi(tmp);
    return(dim);
}

//find shape name from folder name
std::string MainWindow::parseShape(std::string str)
{
    std::string tmp = "";
    for (size_t i = 0; i < str.length(); i++)
    {
        if (!std::isdigit(str[i]))
        {
            tmp.push_back(str[i]);
        }   
    }
    return(tmp);
}
