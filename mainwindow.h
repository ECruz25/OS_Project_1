#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "createprocess_dialog.h"
#include "processor_emulator.h"
#include "processmanager.h"
#include <qobject.h>
#include "math.h"
#include <QTimer>
#include <qsignalmapper.h>
#include "qdebug.h"
#include <vector>
#include <QGraphicsSceneMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ProcessManager* process_manager;
    QStringList m_TableHeader;
//    QTimer* timer;
    ~MainWindow();

public slots:
    void update_process_view();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_create_process_btn_clicked();

    void on_setup_emulator_btn_clicked();

    void on_save_config_btn_clicked();

    void on_kill_btn_clicked();

    void get_process_table();

    void on_creation_time_btn_clicked();

    void update_process_combo();

private:
    Ui::MainWindow *ui;
    CreateProcess_Dialog create_process_window;
    Processor_Emulator process_emulator;
    int quantum;
    int sorter;
    vector<int> processes;
    int present;
    vector<QTimer*> timers;
    vector<double> table_times;
    vector<int> table;
};

#endif // MAINWINDOW_H
