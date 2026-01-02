#include "stm32f103xx.h"

/**
 * @brief 
 * 
 * @param pGPIOx 
 * @param pGPIO_PinConf 
 */
void GPIO_Init(GPIO_Reg_def_t *pGPIOx, GPIO_PinConf_t pGPIO_PinConf)
{
    /* Configure to the pin mode, configuration, output type and output speed */ 

    // CNFy[1:0] MODEy[1:0] = 4bits for each pin: [CNF1 CNF0 MODE1 MODE0]
    uint32_t position = 0;
    uint32_t value = 0;

    if(pGPIO_PinConf.GPIO_PinNumber <= 7)
    {
        position = pGPIO_PinConf.GPIO_PinNumber * 4;

        // Clear the corresponding 4 bits
        pGPIOx->CRL &= ~(0xFU << position);

        // Combine CNF and MODE into the 4-bit field and set it, 0x03 = 0b11
        value = ((uint32_t)(pGPIO_PinConf.GPIO_PinConf & 0x3) << 2) | (uint32_t)(pGPIO_PinConf.GPIO_PinMode & 0x3);
        pGPIOx->CRL |= (value << position);
    }
    else
    {
        position = (pGPIO_PinConf.GPIO_PinNumber - 8) * 4;

        pGPIOx->CRH &= ~(0xFU << position);

        value = ((uint32_t)(pGPIO_PinConf.GPIO_PinConf & 0x3) << 2) | (uint32_t)(pGPIO_PinConf.GPIO_PinMode & 0x3);
        pGPIOx->CRH |= (value << position);
    }

    /* If input with pull-up/pull-down: select pull by ODR bit */
    if((pGPIO_PinConf.GPIO_PinMode == GPIO_MODE_INPUT) && (pGPIO_PinConf.GPIO_PinConf == GPIO_CNF_INPUT_PU_PD))
    {
        if(pGPIO_PinConf.GPIO_PUPD == GPIO_PU)
        {
            pGPIOx->ODR |= (1U << pGPIO_PinConf.GPIO_PinNumber);   // pull-up
        }
        else if(pGPIO_PinConf.GPIO_PUPD == GPIO_PD)
        {
            pGPIOx->ODR &= ~(1U << pGPIO_PinConf.GPIO_PinNumber);  // pull-down
        }
    }
}

/**
 * @brief 
 * 
 * @param pGPIOx 
 * @param PinNumber 
 * @param GPIO_PinState 
 */
void GPIO_WritePin(GPIO_Reg_def_t *pGPIOx, uint8_t PinNumber, GPIO_PinState_t GPIO_PinState)
{
    if (GPIO_PinState == GPIO_PIN_RESET)
    {
        pGPIOx->ODR &= ~(1U << PinNumber);
    }
    else if (GPIO_PinState == GPIO_PIN_SET)
    {
        pGPIOx->ODR |= (0x1U << PinNumber);
    }
}

/**
 * @brief 
 * 
 * @param pGPIOx 
 * @param PinNumber 
 * @return uint8_t 
 */
uint8_t GPIO_ReadPin(GPIO_Reg_def_t *pGPIOx, uint8_t PinNumber)
{
    return (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x1U);
}
