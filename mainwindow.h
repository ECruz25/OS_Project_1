#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "createprocess_dialog.h"
#include "processor_emulator.h"
#include "processmanager.h"
#include <qobject.h>
#include <QTimer>
#include <qsignalmapper.h>
#include "qdebug.h"
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
    QTimer* timer;
    ~MainWindow();

public slots:
    void update_process_view();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_create_process_btn_clicked();

    void on_setup_emulator_btn_clicked();

    void on_save_config_btn_clicked();

    void mousePressEvent(QGraphicsSceneMouseEvent* event)
    {
        if(event->button() == Qt::LeftButton) {
            if(event->modifiers() == Qt::ShiftModifier) {
                qDebug() << "Custom item left clicked with shift key.";
                // add the item to the selection
//                setSelected(true);
            } else if(event->modifiers() == Qt::AltModifier){
                qDebug() << "Custom item left clicked with alt key.";
                // resize the item
//                double radius = boundingRect().width() / 2.0;
//                _center = QPointF(boundingRect().topLeft().x() + pos().x() + radius, boundingRect().topLeft().y() + pos().y() + radius);
//                QPointF pos = event->scenePos();
//                qDebug() << boundingRect() << radius << this->pos() << pos << event->pos();
//                double dist = sqrt(pow(_center.x()-pos.x(), 2) + pow(_center.y()-pos.y(), 2));
//                if(dist / radius > 0.8) {
//                    qDebug() << dist << radius << dist / radius;
//                    _isResizing = true;
//                } else {
//                    _isResizing = false;
//                }
            } else {
                qDebug() << "Custom item left clicked.";
//                QGraphicsItem::mousePressEvent(event);
//                event->accept();
            }
        } else if(event->button() == Qt::RightButton) {
            qDebug() << "Custom item right clicked.";
//            event->ignore();
    }
    }

    void on_kill_btn_clicked();

private:
    Ui::MainWindow *ui;
    CreateProcess_Dialog create_process_window;
    Processor_Emulator process_emulator;
    int quantum;
    int sorter;
    int* processes;
    int present;
};

#endif // MAINWINDOW_H
