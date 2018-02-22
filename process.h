#ifndef PROCESS_H
#define PROCESS_H

#include <QString>
#include <iostream>

using namespace std;

class Process
{
public:
    Process();
    Process(QString name, int execution_time, int priority, int process_id);
    Process* previous;
    Process* next;
    int process_id;
    int priority;
    int execution_time;
    int creation_order;
    QString state;
    QString name;
};

#endif // PROCESS_H
