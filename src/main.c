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

    // GPIO_LockPin(GPIOC, GPIO_PIN_NUM_13);

    // Turn on LED PC13
    GPIO_WritePin(GPIOC, GPIO_PIN_NUM_13, GPIO_PIN_RESET);

    while(1)
    {
        // Read Button PA0 state
        if(GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == GPIO_PIN_SET)
        {
            // Delay some ms
            for (int i = 0; i < 100000; i++);
            if (GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == GPIO_PIN_SET)
            {
                // Change Pin PC13 mode
                // LED PC13 will be turned off if LCKR is not used for Output mode configuration
                Blinky_LedPC13.GPIO_PinMode = GPIO_MODE_INPUT;
                GPIO_Init(GPIOC, Blinky_LedPC13);
            }
        }
    }

    return 0;
}
