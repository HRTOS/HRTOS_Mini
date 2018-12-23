#include<hrtos_api.h>
void os_enter_critical()
{
    EA=0;
    os_en_cr_count++;
}
void os_exit_critical()
{
    if(os_en_cr_count>=1)
    {
        os_en_cr_count--;
        if(os_en_cr_count==0)
        {
            EA=1;
        }
    }
}
