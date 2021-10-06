#ifndef DETECTIONDIALOG_H
#define DETECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class DetectionDialog;
}

class DetectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetectionDialog(QWidget *parent = nullptr);
    ~DetectionDialog();

private:
    Ui::DetectionDialog *ui;
};

#endif // DETECTIONDIALOG_H
