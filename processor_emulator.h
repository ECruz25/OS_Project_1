#ifndef PROCESSOR_EMULATOR_H
#define PROCESSOR_EMULATOR_H

#include <QDialog>
#include <QGraphicsItem>
#include <stdlib.h>
#include "processmanager.h"

namespace Ui {
class Processor_Emulator;
}

class Processor_Emulator : public QDialog
{
    Q_OBJECT

public:
    explicit Processor_Emulator(QWidget *parent = 0);
    ~Processor_Emulator();
    ProcessManager* process_manager;

private slots:
    void on_setup_emulator_clicked();

private:
    Ui::Processor_Emulator *ui;
};

#endif // PROCESSOR_EMULATOR_H
