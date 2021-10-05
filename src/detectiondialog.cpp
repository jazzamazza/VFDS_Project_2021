#include "detectiondialog.h"
#include "ui_detectiondialog.h"

DetectionDialog::DetectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetectionDialog)
{
    ui->setupUi(this);
}

DetectionDialog::~DetectionDialog()
{
    delete ui;
}
