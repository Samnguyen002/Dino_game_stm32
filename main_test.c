#include "stm32f103xx.h"
 
GPIO_PinConf_t Blinky_LedPC13;
GPIO_PinConf_t Button_PA0;

void GPIO_PC13_Init(void)
{

    /* Enable clock for GPIOC */
    RCC_GPIOC_CLK_EN();

    /* Configure PC13 as Output Push-Pull, Max speed 2MHz */
    Blinky_LedPC13.GPIO_PinNumber = GPIO_PIN_NUM_13;
    Blinky_LedPC13.GPIO_PinMode = GPIO_MODE_OUTPUT_LOW;
    Blinky_LedPC13.GPIO_PinConf = GPIO_CNF_GP_OUTPUT_PP;
    Blinky_LedPC13.GPIO_PUPD = 0;  // Not used for output mode

    GPIO_Init(GPIOC, Blinky_LedPC13);
}

void GPIO_PA0_Init(void)
{
    RCC_GPIOA_CLK_EN();

    Button_PA0.GPIO_PinNumber = GPIO_PIN_NUM_0;
    Button_PA0.GPIO_PinMode = GPIO_MODE_INPUT;
    Button_PA0.GPIO_PinConf = GPIO_CNF_INPUT_PU_PD;
    Button_PA0.GPIO_PUPD = GPIO_NO_PUPD;

    GPIO_Init(GPIOA, Button_PA0);
}

int main (void)
{
	GPIO_PC13_Init();
    GPIO_PA0_Init();

    while(1)
    {
        // GPIO_WritePin(GPIOC, GPIO_PIN_NUM_13, GPIO_PIN_SET);

        if(GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == GPIO_PIN_SET)
        {
            GPIO_WritePin(GPIOC, GPIO_PIN_NUM_13, GPIO_PIN_RESET);
        }
        else
        {
            GPIO_WritePin(GPIOC, GPIO_PIN_NUM_13, GPIO_PIN_SET);
        }

        // Toggle LED state
        if(GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == GPIO_PIN_SET)
        {
            // Toggle LED
            for (int i = 0; i < 100000; i++);
            if (GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == GPIO_PIN_SET)
            {
                GPIO_TogglePin(GPIOC, GPIO_PIN_NUM_13);
            }

            // How to fix button debounce?
            // Case 1: simple software delay:  1ms, 2ms, 5ms or ...
            // Cas2 2: using Capacitorr: normally 0.1uF (100nF) for 1ms debounce.

        }
    }

    return 0;
}


///* Hello_world */
////static uint8_t Hello_world;

////int main ()
////{
////    Hello_world = 1;
////    return 0;
////}

///* volatile */
//static volatile uint8_t flag = 0;

//int main(void)
//{
//	while (1)	// First infinite while loop (flag = 0)
//	{
//		if(flag)
//			break;
//	}
//	while(1) // Second infinite while loop (flag != 0)
//	{
//	}
//	
//}
