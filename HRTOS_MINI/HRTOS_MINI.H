#ifndef _OS_51_H_
#define _OS_51_H_
#define MAX_TASKS 5
typedef struct os_task_control_table
{
    unsigned char os_task_wait_tick;
    unsigned char os_task_stack_top;
} TCB;
extern void os_enter_critical();
extern void os_exit_critical();

extern void os_init(void);
extern void os_task(unsigned char task_id ,unsigned int task_point);
extern void os_wait1(unsigned char ticks);
extern void os_start(void);
extern void os_task_exit(void);
extern void exit_int(void);
extern unsigned char  os_task_stack[MAX_TASKS][8];
extern void hrtos();
#endif
