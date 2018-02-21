#include "processor_emulator.h"
#include "ui_processor_emulator.h"

Processor_Emulator::Processor_Emulator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Processor_Emulator)
{
    ui->setupUi(this);

}

Processor_Emulator::~Processor_Emulator()
{
    delete ui;
}

void Processor_Emulator::on_setup_emulator_clicked()
{

}
