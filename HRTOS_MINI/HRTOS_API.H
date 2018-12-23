#ifndef _OS_52_H_
#define _OS_52_H_
#include <reg52.h>
#include<hrtos_mini.h>
extern  bit os_hrtos_wait;
extern  unsigned char os_en_cr_count;
extern unsigned char code os_map_tbl[];
extern TCB os_tcb[MAX_TASKS];
extern  unsigned char os_task_running_id;
extern  unsigned char os_task_rdy_tbl;
extern unsigned char  os_task_stack[MAX_TASKS][20];
#endif
