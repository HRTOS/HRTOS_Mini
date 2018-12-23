#include<hrtos_api.h>
void os_wait1(unsigned char ticks)
{
    os_enter_critical();
    os_tcb[os_task_running_id].os_task_wait_tick = ticks;
    os_task_rdy_tbl &= ~os_map_tbl[os_task_running_id];
    os_exit_critical();
    os_task_exit();
}
