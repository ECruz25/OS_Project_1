#include "processmanager.h"

ProcessManager::ProcessManager()
{
    first = NULL;
    last = NULL;
    size = 0;
}

void ProcessManager::add_process(Process* process)
{
    if(first == NULL)
    {
        first = process;
        last = process;
        size++;
        return;
    }
    last->next = process;
    process->previous= last;
    last = process;
    size++;
}

void ProcessManager::delete_process(Process* process)
{
    if(this->first == process)
    {
        this->first = process->next;
        process = NULL;
    }
    else if (this->last == process)
    {
        this->last = process->previous;
        process = NULL;
    }
    else
    {
        process->previous->next = process->next->previous;
    }
}

void ProcessManager::get_processes(Process* process)
{
    if(process->next!= NULL)
    {
        cout<<",";
        get_processes(process->next);
    }
}

Process* ProcessManager::get_first_process()
{
    return first;
}

void ProcessManager::sort_by_priority()
{
    Process *ptr, *dummy = new Process();

    if(first==NULL)
    {
        return;
    }
    if(first->next==NULL)
    {
        return;
    }

    int swapped = 1;

    while (swapped)
    {
        swapped = 0;

        ptr = first;
        while (ptr->next != NULL) {
            if (ptr->priority < ptr->next->priority)
            {
                swapped = 1;

                dummy->name = ptr->name;
                ptr->name = ptr->next->name;
                ptr->next->name = dummy->name;

                dummy->execution_time = ptr->execution_time;
                ptr->execution_time = ptr->next->execution_time;
                ptr->next->execution_time = dummy->execution_time;

                dummy->priority = ptr->priority;
                ptr->priority = ptr->next->priority;
                ptr->next->priority = dummy->priority;
            }
            ptr = ptr->next;
        }
    }
    cout<<first->execution_time<<" - "<<last->execution_time<<endl;
}

void ProcessManager::sort_by_execution_time()
{
    Process *ptr, *dummy = new Process();

    if(first==NULL)
    {
        return;
    }
    if(first->next==NULL)
    {
        return;
    }

    int swapped = 1;

    while (swapped)
    {
        swapped = 0;

        ptr = first;
        while (ptr->next != NULL) {
            if (ptr->execution_time > ptr->next->execution_time)
            {
                swapped = 1;

                dummy->name = ptr->name;
                ptr->name = ptr->next->name;
                ptr->next->name = dummy->name;

                dummy->execution_time = ptr->execution_time;
                ptr->execution_time = ptr->next->execution_time;
                ptr->next->execution_time = dummy->execution_time;

                dummy->priority = ptr->priority;
                ptr->priority = ptr->next->priority;
                ptr->next->priority = dummy->priority;
            }
            ptr = ptr->next;
        }
    }
}
