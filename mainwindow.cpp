#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int num = 2;
    cout<<floor(num/5)+(num%5==0?0:1)<<endl;
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
    ui->priority_edit->clear();
    ui->processes_combo->clear();
    update_process_combo();
}

void MainWindow::on_setup_emulator_btn_clicked()
{
//    processes = new int[process_manager->size];

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
        process_manager->sort_by_mix();
        break;
    default:
        break;
    }

    proc = process_manager->first;

    int count = 0;
    while(proc!=NULL)
    {
        if(proc->creation_order >= 0)
        {
            processes.push_back(proc->process_id);
//            timers.push_back(new QTimer(this));
        }
        proc = proc->next;
        count++;
    }

    delete proc;
    get_process_table();

    ui->tableWidget->setRowCount(process_manager->size);
    ui->tableWidget->setColumnCount(5);
    m_TableHeader<<"Id"<<"Nombre"<<"Prioridad"<<"Tiempo CPU"<<"Estado";
    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);

    present = -1;
    int time_tracker = 0;
    update_process_view();

    present = 0;
    for(int x = 0; x < table.size(); x++)
    {
        int time = table_times.at(x) * 1000;
        timers.at(x)->setInterval(time_tracker + time);
        timers.at(x)->setSingleShot(true);
        connect(timers.at(x), SIGNAL(timeout()), SLOT(update_process_view()));
        timers.at(x)->start();
//        timer->setInterval(time);
//        timer->setSingleShot(true);
//        connect(timer, SIGNAL(timeout()), SLOT(update_process_view()));
//        timer->start();
//        QTimer::singleShot(time_tracker + time, this, SLOT(update_process_view()));
        time_tracker = time_tracker + time;
    }
    for(int x = 0; x < timers.size(); x++)
    {
        cout<<table.at(x)<<endl;
    }
}

void MainWindow::update_process_view()
{
    cout<<"updating: "<<processes[present]<<endl;
    if(present>=0)
    {
        table.at(present) = -1;
    }
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsItemGroup* group = new QGraphicsItemGroup();

    for(int x = 0; x < table.size(); x++)
    {
        if(table.at(x) != -1)
        {
            QGraphicsRectItem* rect = new QGraphicsRectItem(0 + (x*(ui->graphicsView->width() / table.size())),
                                                            0,
                                                            (ui->graphicsView->width() / table.size()) - 10,
                                                            50);
            QGraphicsTextItem* text = new QGraphicsTextItem();
            rect->setBrush(QBrush(Qt::green));
            text->setPos(0 + (x*(ui->graphicsView->width() / table.size())), 10);
            text->setPlainText(QString::number(process_manager->get_process_by_id(int(table.at(x)),process_manager->first)->process_id));
            group->addToGroup(rect);
            group->addToGroup(text);
            ui->tableWidget->setItem( x, 0, new QTableWidgetItem(QString::number(process_manager->get_process_by_id(int(table.at(x)),process_manager->first)->process_id)));
            ui->tableWidget->setItem( x, 1, new QTableWidgetItem(process_manager->get_process_by_id(int(table.at(x)),process_manager->first)->name));
            ui->tableWidget->setItem( x, 2, new QTableWidgetItem(QString::number(process_manager->get_process_by_id(int(table.at(x)),process_manager->first)->priority)));
            ui->tableWidget->setItem( x, 3, new QTableWidgetItem(QString::number(process_manager->get_process_by_id(int(table.at(x)),process_manager->first)->execution_time)));
            ui->tableWidget->setItem( x, 4, new QTableWidgetItem(process_manager->get_process_by_id(int(table.at(x)),process_manager->first)->state));
        }
    }
    scene->addItem(group);
    ui->graphicsView->setScene(scene);
    cout<<"present: "<<present<<endl;
    present = present + 1;
}

void MainWindow::on_save_config_btn_clicked()
{
    sorter = ui->sorter_combo->currentText() == "Prioridad" ? 1 : ui->sorter_combo->currentText() == "Mixto" ? 3 : 2;
    quantum = ui->quantum_edit->text().toInt();
}

void MainWindow::on_kill_btn_clicked()
{
    int process_to_kill = ui->kill_edit->text().toInt();
    for(int x = 0; x < processes.size(); x++)
    {
        if(processes.at(x) == process_to_kill)
        {
            for(int y=x+1; y < processes.size(); y++)
            {
                timers.at(y)->setInterval(timers.at(y)->remainingTime() - timers.at(x)->remainingTime());
            }
            processes.at(x) = -1;
            present = present - 1;
            update_process_view();
            timers.at(x)->stop();
        }
    }
}

void MainWindow::get_process_table()
{
    vector<int> process_positions;

    for(int x = 0; x < processes.size(); x++)
    {
        int exec_time = process_manager->get_process_by_id(int(processes.at(x)),process_manager->first)->execution_time;
        int positions = floor(exec_time / quantum) + (exec_time % quantum == 0 ? 0 : 1);
        process_positions.push_back(positions);
    }

    for(int x = 0; x < processes.size(); x++)
    {
        Process* process = process_manager->get_process_by_id(int(processes.at(x)),process_manager->first);
        int positions = process_positions.at(x);
        int exec_time = process->execution_time;
        for(int y = 0; y < positions; y++)
        {
            if(process->state != "Blocked")
            {
                table.push_back(processes.at(x));
                timers.push_back(new QTimer(this));
                if(exec_time%quantum == 0)
                {
                    table_times.push_back(floor(exec_time / quantum));
                    exec_time = exec_time - (floor(exec_time / quantum));
                }
                else
                {
                    table_times.push_back(exec_time);
                }
                if(process_positions.at(x) > 1)
                {
                    process->state = "Blocked";
                }
                process_positions.at(x) = process_positions.at(x) - 1;
            }
            else
            {
                if(processes.at(x)==processes.back())
                {
                    process->state = "Ready";
                }
                else
                {
                    int z = x + 1;
                    while(processes.at(x)!=processes.back())
                    {
                        if(process_positions.at(z) >= 1)
                        {
                            table.push_back(processes.at(z));
                            timers.push_back(new QTimer(this));
                            if(exec_time%quantum == 0)
                            {
                                table_times.push_back(floor(exec_time / quantum));
                                exec_time = exec_time - (floor(exec_time / quantum));
                            }
                            else
                            {
                                table_times.push_back(exec_time);
                            }
                            process_positions.at(z) = process_positions.at(z) - 1;
                            process->state = "Ready";
                            break;
                        }
                        else if(processes.at(z)==processes.back())
                        {
                            process->state = "Ready";
                            break;
                        }
                        else
                        {
                            z++;
                        }
                    }
                }
                y--;
            }
        }



//        int exec_time = process_manager->get_process_by_id(int(processes.at(x)),process_manager->first)->execution_time;
//        if(process_positions.at(x) == 1)
//        {
//            table.push_back(processes.at(x));
//            process_positions.at(x) = 0;
//        }
//        if (process_positions.at(x) > 1)
//        {
//            for(int y = 0; y < process_positions.at(x); y++)
//            {
//                Process* process = process_manager->get_process_by_id(int(processes.at(x)),process_manager->first);
//                if(process->state!="Blocked")
//                {
//                    table.push_back(processes.at(x));
//                    process_manager->get_process_by_id(int(processes.at(x)),process_manager->first)->state = "Blocked";
//                }
//                if(processes.at(x)!=processes.back())
//                {
//                    if(process_positions.at(x+1)>0)
//                    {
//                        table.push_back(processes.at(x+1));
//                        process_positions.at(x+1) = process_positions.at(x+1) - 1 ;
//                    }
//                    process_manager->get_process_by_id(int(processes.at(x)),process_manager->first)->state = "Ready";
//                }
//                if(y == process_positions.at(x) - 1)
//                {
//                    process_positions.at(x) = 0;
//                }
//            }
//        }
    }
    for(int x = 0; x < table.size(); x++)
    {
        cout<<table.at(x)<<",";
    }
    cout<<endl;
}

void MainWindow::on_creation_time_btn_clicked()
{
    Process* proc;
    proc = process_manager->first;

    int count = 0;
    while(proc!=NULL)
    {
        if(proc->name == ui->processes_combo->currentText())
        {
            proc->creation_order = ui->creation_time_edit->text().toInt();
        }
        proc = proc->next;
        count++;
    }

    delete proc;
}

void MainWindow::update_process_combo()
{
    Process* proc;
    proc = process_manager->first;

    int count = 0;
    while(proc!=NULL)
    {
        ui->processes_combo->addItem(proc->name);
        proc = proc->next;
        count++;
    }

    delete proc;
}
