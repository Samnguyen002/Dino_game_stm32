#include <stdint.h>

/* Hello_world */
//static uint8_t Hello_world;

//int main ()
//{
//    Hello_world = 1;
//    return 0;
//}

/* volatile */
static volatile uint8_t flag = 0;

int main(void)
{
	while (1)	// First infinite while loop (flag = 0)
	{
		if(flag)
			break;
	}
	while(1) // Second infinite while loop (flag != 0)
	{
	}
}
