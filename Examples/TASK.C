#include <reg51.h>
#include<hrtos_mini.h>
void task_0(void)
{
    while(1)
    {
        P0=0;
		hrtos();
    }
}
void task_1(void)
{
    while(1)
    {
        P0=1;
		hrtos();
    }
}
void task_2(void)
{
    while(1)
    {
        P0 = 0x3;
		hrtos();
    }
}
void task_3(void)
{
    while(1)
    {
        P0 = 7;
		hrtos();
    }
}
void task_4(void)
{
    while(1)
    {
        P0 = 15;
		hrtos();
    }
}
void main()
{
    os_init();
    os_task(0,task_0);
    os_task(1,task_1);
    os_task(2,task_2);
    os_task(3,task_3);
    os_task(4,task_4);
    os_start();	while(1);
}
