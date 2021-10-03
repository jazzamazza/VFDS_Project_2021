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
    setFixedSize(500,500);

    setupCoreWidgets();
    createMenus();

    centralWidgetLayout->addLayout(formLayout);
    //centralWidgetLayout->addWidget(mainWidget);
    centralWidgetLayout->addLayout(buttonsLayout);
    mainWidget->setLayout(centralWidgetLayout);

    setCentralWidget(mainWidget);

    setupSignalsAndSlots();
    

}

MainWindow::~MainWindow()
{
}

void MainWindow::setupCoreWidgets(){
    //Setup Widgets and Layout
    mainWidget = new QWidget();
    centralWidgetLayout = new QVBoxLayout();
    formLayout = new QGridLayout();
    buttonsLayout = new QHBoxLayout();

    //Setup labels
    fileLabel = new QLabel("File:");
    partDisplayLabel = new QLabel("PART DISPLAYED HERE");
    imageLabel = new QLabel("PART");

    //Setup buttons
    loadPushButton = new QPushButton("Load");
    nextPushButton = new QPushButton("Next");
    backPushButton = new QPushButton("Back");

    //Setup input
    fileLineEdit = new QLineEdit();

    //Layout
    formLayout->addWidget(fileLabel, 0, 0);
    formLayout->addWidget(fileLineEdit,0,1);
    formLayout->addWidget(imageLabel,1,0);

    buttonsLayout->addStretch();
    buttonsLayout->addWidget(loadPushButton);
    buttonsLayout->addWidget(nextPushButton);
    buttonsLayout->addWidget(backPushButton);
    
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
    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutDialog);
    connect(loadPushButton, SIGNAL(clicked()), this, SLOT(loadButtonClicked()));
    //connect(clearPushButton, SIGNAL(clicked()), this, SLOT(clearAllRecords()));
    //connect(loadPushButton, &QAction::triggered, this, &MainWindow::loadButtonClicked);
}

void MainWindow::loadButtonClicked()
{

    //QMessageBox::information(this, "VFDS System", "VFDS INFORMATION", QMessageBox::Ok|QMessageBox::Default, QMessageBox::NoButton, QMessageBox::NoButton);
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"", tr("Images (*.pgm *.png)"));

    if (QString::compare(filename, QString()) != 0)
    {
        //QImage image;
        bool valid = image.load(filename);

        if(valid)
        {
           imageLabel->setPixmap(QPixmap::fromImage(image));
           QMessageBox::information(this,"File Name", filename,QMessageBox::Ok,QMessageBox::Default);
        }
        else
        {
            //something
        }
    }
}

void MainWindow::aboutDialog()
{

    QMessageBox::about(this, "About VFDS System",
                        "RMS System 2.0"
                        "<p>Copyright &copy; 2005 Inc."
                        "This is a simple application to demonstrate the use of windows,"
                        "tool bars, menus and dialog boxes");
}

//find image dimension from folder name
int parseDim(std::string str)
{
    int dim = 0;
    std::string tmp = "";
    //for (int i = str.length()-3; i < str.length(); i++)
    for (int i = 0; i < str.length(); i++)
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
std::string parseShape(std::string str)
{
    std::string tmp = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (!std::isdigit(str[i]))
        {
            tmp.push_back(str[i]);
        }   
    }
    return(tmp);
}
