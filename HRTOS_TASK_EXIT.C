#include<hrtos_api.h>
void os_task_exit(void)
{
    EA = 0;
    os_hrtos_wait=0;
    TF0=1;
    EA = 1;
}
