#include "detectiondialog.h"
#include "ui_detectiondialog.h"

void DetectionDialog::atChecked()
{

}

void DetectionDialog::okClick()
{

}

DetectionDialog::DetectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetectionDialog)
{
    ui->setupUi(this);
    sigm = ui->doubleSpinBox_m->value();
    sigs = ui->doubleSpinBox_s->value();
    activated = ui->checkBox_AThreshold->isChecked();

    //connect(this,&ui->fractureDetectionButtonBox->Ok,parent,SLOT())
}

DetectionDialog::~DetectionDialog()
{
    delete ui;
}
