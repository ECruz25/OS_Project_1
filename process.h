#ifndef PROCESS_H
#define PROCESS_H

#include <QString>
#include <iostream>

using namespace std;

class Process
{
public:
    Process();
    Process(QString name, int execution_time, int priority);
    Process* previous;
    Process* next;
    int priority;
    int execution_time;
    QString state;
    QString name;
};

#endif // PROCESS_H
