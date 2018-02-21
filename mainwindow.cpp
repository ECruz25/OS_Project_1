#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    process_manager = new ProcessManager();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    create_process_window.show();
}

void MainWindow::on_pushButton_2_clicked()
{
    process_emulator.show();
}

void MainWindow::on_create_process_btn_clicked()
{
    process_manager->add_process(new Process(ui->name_edit->text(),
                                             ui->exec_edit->text().toInt(),
                                             ui->priority_edit->text().toInt(),
                                             process_manager->create_process_id(rand()%5000+1)));
    ui->name_edit->clear();
    ui->exec_edit->clear();
    ui->priority_edit->clear();}

void MainWindow::on_setup_emulator_btn_clicked()
{
    processes = new int[process_manager->size];

    Process* proc;

    switch (sorter) {
    case 1:
        process_manager->sort_by_priority();
        break;
    case 2:
        process_manager->sort_by_execution_time();
        break;
    case 3:
        //cambiar a mixto
        process_manager->sort_by_priority();
        break;
    default:
        break;
    }

    proc = process_manager->first;

    int count = 0;
    while(proc!=NULL)
    {
        processes[count] = proc->process_id;
        proc = proc->next;
        count++;
    }

    delete proc;

    ui->tableWidget->setRowCount(process_manager->size);
    ui->tableWidget->setColumnCount(5);
    m_TableHeader<<"Id"<<"Nombre"<<"Prioridad"<<"Tiempo CPU"<<"Estado";
    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);

    present = -1;
    int timer = 0;
    update_process_view();

    present = 0;
    for(int x = 0; x < process_manager->size; x++)
    {
        int time = process_manager->get_process_by_id(int(processes[x]),process_manager->first)->execution_time * 1000;
        QTimer::singleShot(timer + time, this, SLOT(update_process_view()));
        timer = timer + time;
    }
}

void MainWindow::update_process_view()
{
    if(present>=0)
    {
        processes[present] = -1;
    }
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsItemGroup* group = new QGraphicsItemGroup();

    for(int x = 0; x < process_manager->size; x++)
    {
        if(processes[x] != -1)
        {
            QGraphicsRectItem* rect = new QGraphicsRectItem(0 + (x*(ui->graphicsView->width() / process_manager->size))
                                                            ,0
                                                            ,(ui->graphicsView->width() / process_manager->size) - 10
                                                            ,50);
            QGraphicsTextItem* text = new QGraphicsTextItem();
            rect->setBrush(QBrush(Qt::green));
            text->setPos(0 + (x*(ui->graphicsView->width() / process_manager->size)), 10);
            text->setPlainText(QString::number(process_manager->get_process_by_id(int(processes[x]),process_manager->first)->process_id));
            group->addToGroup(rect);
            group->addToGroup(text);
            ui->tableWidget->setItem( x, 0, new QTableWidgetItem(QString::number(process_manager->get_process_by_id(int(processes[x]),process_manager->first)->process_id)));
            ui->tableWidget->setItem( x, 1, new QTableWidgetItem(process_manager->get_process_by_id(int(processes[x]),process_manager->first)->name));
            ui->tableWidget->setItem( x, 2, new QTableWidgetItem(QString::number(process_manager->get_process_by_id(int(processes[x]),process_manager->first)->priority)));
            ui->tableWidget->setItem( x, 3, new QTableWidgetItem(QString::number(process_manager->get_process_by_id(int(processes[x]),process_manager->first)->execution_time)));
            ui->tableWidget->setItem( x, 4, new QTableWidgetItem(process_manager->get_process_by_id(int(processes[x]),process_manager->first)->state));
        }
    }
    scene->addItem(group);
    ui->graphicsView->setScene(scene);
    present = present + 1;
}

void MainWindow::on_save_config_btn_clicked()
{
    sorter = ui->sorter_combo->currentText() == "Prioridad" ? 1 : ui->sorter_combo->currentText() == "Mixto" ? 3 : 2;
    quantum = ui->quantum_edit->text().toInt();
    cout<<sorter<<" "<<quantum<<endl;
}

void MainWindow::on_kill_btn_clicked()
{
    int process_to_kill = ui->kill_edit->text().toInt();
    if(processes[process_to_kill] != NULL)
    {
        processes[process_to_kill] = -1;
        present = present + 1;
        update_process_view();
    }
}
