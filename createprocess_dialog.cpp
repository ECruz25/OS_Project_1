#include "createprocess_dialog.h"
#include "ui_createprocess_dialog.h"

CreateProcess_Dialog::CreateProcess_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProcess_Dialog)
{
    ui->setupUi(this);
    process_manager = new ProcessManager();
}

CreateProcess_Dialog::~CreateProcess_Dialog()
{
    delete ui;
}

void CreateProcess_Dialog::on_buttonBox_accepted()
{
    process_manager->add_process(new Process(ui->name_edit->text(), ui->exec_edit->text().toInt(), ui->priority_edit->text().toInt(), process_manager->create_process_id(rand()%5000+1)));
    if(process_manager->size>=5) process_manager->sort_by_priority();
    ui->name_edit->clear();
    ui->exec_edit->clear();
    ui->priority_edit->clear();
}
