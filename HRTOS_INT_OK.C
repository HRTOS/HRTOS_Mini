#include<reg51.h>
void hrtos()
{
	char i;
	ET0=1;
	i=2;
	ET0=0;
}