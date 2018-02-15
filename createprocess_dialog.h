#ifndef CREATEPROCESS_DIALOG_H
#define CREATEPROCESS_DIALOG_H

#include <QDialog>
#include "processmanager.h"
#include "iostream"

using namespace std;

namespace Ui {
class CreateProcess_Dialog;
}

class CreateProcess_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProcess_Dialog(QWidget *parent = 0);
    ~CreateProcess_Dialog();
    ProcessManager* process_manager;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CreateProcess_Dialog *ui;
};

#endif // CREATEPROCESS_DIALOG_H
