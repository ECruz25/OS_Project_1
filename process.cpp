#include "process.h"
Process::Process()
{

}

Process::Process(QString name, int execution_time, int priority, int process_id)
{
    this->execution_time = execution_time;
    this->priority = priority;
    this->name = name;
    this->process_id = process_id;
    this->state = "Ready";
    this->creation_order = 0;
    this->next = NULL;
    this->previous = NULL;
}
