/*
Jared May
25/09/2021
VFDS Main Window
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>

#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QtGui>
#include <Qt>

#include <QLineEdit>
#include <QMessageBox>

#include <QScrollArea>
#include <QFileDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        bool loadFile(const QString &);

    private slots:
        //void open();
        //void saveAs();
        /*void print();
        void copy();
        void paste();
        void zoomIn();
        void zoomOut();
        void normalSize();
        void fitToWindow();*/
        //void about();
        void aboutDialog();
        void loadButtonClicked();

    private:
    
        //driver functions
        int parseDim(std::string str);
        std::string parseShape(std::string str);

        // Init Methods
        void setupSignalsAndSlots();
        void setupCoreWidgets();
        void createMenus();
        /*
        void createActions();
        void createMenus();
        void updateActions();
        bool saveFile(const QString &fileName);
        void setImage(const QImage &newImage);
        void scaleImage(double factor);
        void adjustScrollBar(QScrollBar *scrollBar, double factor);
    */
        QImage image;
        QLabel *imageLabel;
        QScrollArea *scrollArea;
        double scaleFactor = 1;

/*
    QAction *saveAsAct;
    QAction *printAct;
    QAction *copyAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    */   

        // Layout and Widgets
        QWidget *mainWidget;
        QVBoxLayout *centralWidgetLayout;
        QGridLayout *formLayout;
        QHBoxLayout *buttonsLayout;

        // Menus
        QMenu *fileMenu;
        QMenu *helpMenu;

        // Actions
        QAction *quitAction;
        QAction *aboutAction;
        QAction *openAction;
        //QAction *cancelAction;
        //QAction *newAction;

        // GUI 
        //Labels
        QLabel *fileLabel;
        QLabel *partDisplayLabel;

        //Buttons
        QPushButton *loadPushButton;
        QPushButton *nextPushButton;
        QPushButton *backPushButton;

        //Input
        QLineEdit *fileLineEdit;
};
#endif // MAINWINDOW_H
