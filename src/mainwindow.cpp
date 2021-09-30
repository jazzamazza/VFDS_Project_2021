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

    //Setup buttons
    loadPushButton = new QPushButton("Load");
    nextPushButton = new QPushButton("Next");
    backPushButton = new QPushButton("Back");

    //Setup input
    fileLineEdit = new QLineEdit();

    //Layout
    formLayout->addWidget(fileLabel, 0, 0);
    formLayout->addWidget(fileLineEdit,0,1);

    buttonsLayout->addStretch();
    buttonsLayout->addWidget(loadPushButton);
    buttonsLayout->addWidget(nextPushButton);
    buttonsLayout->addWidget(backPushButton);
    
}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu("&File");
    quitAction = new QAction("Quit", this);
    quitAction->setShortcuts(QKeySequence::Quit);
    //newAction = new QAction("&New", this);
    //newAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    openAction = new QAction("&Open", this);
    openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    helpMenu = menuBar()->addMenu("Help");
    aboutAction = new QAction("About", this);
    aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    helpMenu->addAction(aboutAction);

}

void MainWindow::setupSignalsAndSlots() {
    // Setup Signals and Slots
    connect(quitAction, &QAction::triggered, this, &QApplication::quit);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutDialog()));
    connect(loadPushButton, SIGNAL(clicked()), this, SLOT(loadButtonClicked()));
    //connect(clearPushButton, SIGNAL(clicked()), this, SLOT(clearAllRecords()));
}

void MainWindow::loadButtonClicked()
{

    QMessageBox::information(this, tr("RMS System"), tr("Record saved successfully!"),
                             QMessageBox::Ok|QMessageBox::Default,
                             QMessageBox::NoButton, QMessageBox::NoButton);


}

void MainWindow::aboutDialog()
{

    QMessageBox::about(this, "About RMS System",
                       "RMS System 2.0"
                          "<p>Copyright &copy; 2005 Inc."
                          "This is a simple application to demonstrate the use of windows,"
                          "tool bars, menus and dialog boxes");
}