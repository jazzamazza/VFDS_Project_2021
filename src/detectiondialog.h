#ifndef DETECTIONDIALOG_H
#define DETECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class DetectionDialog;
}

class DetectionDialog : public QDialog
{
    Q_OBJECT

public slots:
    void atChecked();
    void okClick();

signals:

public:
    explicit DetectionDialog(QWidget *parent = nullptr);
    ~DetectionDialog();
    double sigm;
    double sigs;
    bool activated;

private:
    Ui::DetectionDialog *ui;
};

#endif // DETECTIONDIALOG_H
