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

class MainWindow : public QMainWindow
{

Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool loadFile(const QString &);

private slots:
    void open();
    void about();

private:
    // Init Methods
    void setupSignalsAndSlots();
    void setupCoreWidgets();
    void createActions();
    void createMenus();
    void updateActions();
    bool saveFile(const QString &fileName);
    void setImage(const QImage &newImage);

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
    QAction *cancelAction;
    QAction *newAction;

    // GUI 
    QLabel *fileLabel;
    QLabel *partDisplayLabel;
    QPushButton *loadPushButton;
    QPushButton *nextPushButton;
    QPushButton *backPushButton;
};
#endif // MAINWINDOW_H
