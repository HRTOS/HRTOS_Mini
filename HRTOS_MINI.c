#include <reg52.h>
#include<hrtos_mini.h>
#define OS_ST 9	  //保存的堆栈数
unsigned char os_en_cr_count;
unsigned char code os_map_tbl[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
TCB os_tcb[MAX_TASKS];
unsigned char os_task_running_id;//当前运行的任务号
unsigned char os_task_rdy_tbl;//任务状态
unsigned char  os_task_stack[MAX_TASKS][8];//任务堆栈区
unsigned char os_hrtos_stack[26];//HRTOS堆栈区
unsigned char os_stack;//堆栈初始值
bit os_hrtos_wait;
void timer0_isr(void) interrupt 1
{
    unsigned char i,j;
    TF0=0;
	if(os_task_running_id==MAX_TASKS)
	{
		ET0=0;
		i=0;
		goto OS_HRT;
	}
    os_tcb[os_task_running_id].os_task_stack_top=SP;
    j= SP-OS_ST-os_stack;
    if(os_hrtos_wait)
    {
        for(i=0; i<MAX_TASKS; i++)
        {
            if(os_tcb[i].os_task_wait_tick)
            {
                os_tcb[i].os_task_wait_tick--;
                if(os_tcb[i].os_task_wait_tick == 0)
                {
                    os_task_rdy_tbl |= os_map_tbl[i];
                }
            }
        }
    }
    else { os_hrtos_wait=1; }
    for(i=0; i<j; i++)   //保护
    {
        os_task_stack[os_task_running_id][i]=os_hrtos_stack[i];
    }
    for (i=os_task_running_id+1; i<MAX_TASKS; i++)//筛选
    {
        if(os_task_rdy_tbl&os_map_tbl[i])
        {
            break;
        }
    }
    if(i==MAX_TASKS)
    {
 		for (i=0; i<=os_task_running_id; i++)
        {
            if(os_task_rdy_tbl&os_map_tbl[i])
            {
                break;
            }
        }
    }
OS_HRT:
	os_task_running_id = i;//选择
    j= os_tcb[os_task_running_id].os_task_stack_top-OS_ST-os_stack;
    for(i=0; i<j; i++)   //恢复
    {
        os_hrtos_stack[i]=os_task_stack[os_task_running_id][i];
    }
    SP = os_tcb[os_task_running_id].os_task_stack_top;
}
void os_init(void)
{
    EA = 0;
    ET0 = 1;
    TMOD|=0X01;
    TH0 = 0x00;
    TL0 = 0x00;
    os_task_rdy_tbl = 0;
    os_stack=(unsigned char)os_hrtos_stack;
	os_stack--;
    os_hrtos_wait=1;
    os_en_cr_count = 0;
}
void os_task(unsigned char task_id ,unsigned int task_point)
{
    os_enter_critical();
    os_task_stack[task_id][0] = task_point;//地址
    os_task_stack[task_id][1] = task_point>>8;
    os_tcb[task_id].os_task_stack_top = os_stack+11;
    os_task_rdy_tbl |= os_map_tbl[task_id];//生效
    os_tcb[task_id].os_task_wait_tick = 0; //延时
    os_exit_critical();
}
void os_start(void)
{
    os_task_running_id = MAX_TASKS;
    os_hrtos_stack[0]=os_task_stack[0][0];
    os_hrtos_stack[1]=os_task_stack[0][1];
    EA = 1;
    TR0 = 1;
}
