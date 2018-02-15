#include "process.h"
Process::Process()
{

}

Process::Process(QString name, int execution_time, int priority)
{
    this->execution_time = execution_time;
    this->priority = priority;
    this->name = name;
    this->state = "Ready";
    this->next = NULL;
    this->previous = NULL;
}
