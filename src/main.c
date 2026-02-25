#include "stm32f103xx.h"
 
static GPIO_PinConf_t Blinky_LedPC13;
static GPIO_PinConf_t Button_PA0;

/**
 * @brief Simple delay function. It uses for loop to excute a delay.
 *        Change the number of loop cycle to increase or decrease the delay time.
 * 
 */
static void SimpleDelay(void)
{
    uint32_t delay_count;
    for (delay_count = 0; delay_count < 20000000; delay_count++)
    {

    }
}

static void GPIO_PC13_Init(void)
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

/* Button */
static void GPIO_PA0_Init(void)
{
    RCC_GPIOA_CLK_EN();

    Button_PA0.GPIO_PinNumber = GPIO_PIN_NUM_0;
    Button_PA0.GPIO_PinMode = GPIO_MODE_INPUT;
    Button_PA0.GPIO_PinConf = GPIO_CNF_INPUT_PU_PD;
    Button_PA0.GPIO_PUPD = GPIO_NO_PUPD;
    Button_PA0.GPIO_EdgeTrigger = GPIO_IT_EDGE_RT;

    GPIO_Init(GPIOA, Button_PA0);
    GPIO_IT_Init(GPIOA, Button_PA0, 1);
}

int main (void)
{
	GPIO_PC13_Init();
    GPIO_PA0_Init();

    while(1)
    {
        // Do nothing
    }

    return 0;
}

/**
 * @brief This function is ISR function of respective EXTIO interrupt.
 * 
 */
static void EXTI0_IRQHandler(void)
{
    /* Is the corresponding bit in EXTI_PR set or not */
    if ((EXTI->PR >> Button_PA0.GPIO_PinNumber) & 0x1U)
    {
        /* Clear the pending bit by writing 1 */
        EXTI->PR |= (0x01U << Button_PA0.GPIO_PinNumber);
    }

    SimpleDelay();
    if (GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == GPIO_PIN_SET)
    {
        GPIO_TogglePin(GPIOC, GPIO_PIN_NUM_13);
    }
}


