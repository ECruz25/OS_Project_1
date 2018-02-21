#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "process.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

class ProcessManager
{
public:
    ProcessManager();
    void add_process(Process* process);
    void delete_process(Process* process);
    void sort_by_priority();
    void sort_by_execution_time();
    void get_processes(Process* process);
    int create_process_id(int random_number);
    int size;
    bool is_empty();
    Process* get_first_process();
    Process* get_process_by_id(int id, Process* process);
    Process* first;
    Process* last;
};

#endif // PROCESSMANAGER_H
