#include "processor_emulator.h"
#include "ui_processor_emulator.h"

Processor_Emulator::Processor_Emulator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Processor_Emulator)
{
    ui->setupUi(this);
    process_manager = new ProcessManager;

    process_manager->add_process(new Process("Process 1",12,51));
    process_manager->add_process(new Process("Process 2",13,41));
    process_manager->add_process(new Process("Process 3",14,551));
    process_manager->add_process(new Process("Process 4",15,21));
    process_manager->add_process(new Process("Process 5",16,31));
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsItemGroup* group = new QGraphicsItemGroup();

    for(int x = 0; x<process_manager->size;x++){
        QGraphicsRectItem* rect = new QGraphicsRectItem(0 + (x*60),0,50,50);
        rect->setBrush(QBrush(Qt::green));
        group->addToGroup(rect);
        group->addToGroup(line);
    }
    scene->addItem(group);
    ui->graphicsView->setScene(scene);
}

Processor_Emulator::~Processor_Emulator()
{
    delete ui;
}
