#include "stm32f103xx.h"

void GPIO_Init(GPIO_Reg_def_t *pGPIOx, GPIO_PinConf_t pGPIO_PinConf)
{
    /* Configure to the pin mode, configuration, output type and output speed */ 

    // CNFy[1:0] MODEy[1:0] = 4bits for each pin: [CNF1 CNF0 MODE1 MODE0]
    uint32_t position = 0;
    uint32_t value = 0;

    if (pGPIO_PinConf.GPIO_PinNumber <= 7)
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
    if ((pGPIO_PinConf.GPIO_PinMode == GPIO_MODE_INPUT) && (pGPIO_PinConf.GPIO_PinConf == GPIO_CNF_INPUT_PU_PD))
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

uint8_t GPIO_ReadPin(GPIO_Reg_def_t *pGPIOx, uint8_t PinNumber)
{
    return (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x1U);
}

void GPIO_TogglePin(GPIO_Reg_def_t *pGPIOx, uint8_t PinNumber)
{
    pGPIOx->ODR ^= (0x01U << PinNumber);
}

void GPIO_WritePinBit(GPIO_Reg_def_t *pGPIOx, uint8_t PinNumber, GPIO_PinState_t GPIO_PinState)
{
    if (GPIO_PinState == GPIO_PIN_SET)
    {
        pGPIOx->BSRR |= (0X1U << PinNumber);
    }
    else
    {
        pGPIOx->BSRR |= (0X1U << (PinNumber + 16U));
    }
}

void GPIO_LockPin(GPIO_Reg_def_t *pGPIOx, uint8_t PinNumber)
{
    uint32_t temp1 = (0x01U << 16U);
    uint32_t temp2 = (0x01U << PinNumber);  

    temp1 |= temp2;

    // LOCK KEY WRITING SEQUENCE
    // WR LCKR[16] = '1' + LCKR[15:0]
    pGPIOx->LCKR = temp1;
    // WR LCKR[16] = '0' + LCKR[15:0]
    pGPIOx->LCKR = temp2;
    // WR LCKR[16] = '1' + LCKR[15:0]
    pGPIOx->LCKR = temp1;
    // RD LCKR[16] 
    temp1 = pGPIOx->LCKR;
}

void GPIO_IT_Init(GPIO_Reg_def_t *pGPIOx, GPIO_PinConf_t pGPIO_PinConf, uint8_t IRQPriority)
{
    uint8_t index = 0, bit_pos = 0;
    uint8_t port_code;
    /* Configure the AFIO_EXTICR (input for EXTI line) */
    // Enable AFIO clock
    RCC_AFIO_CLK_EN();
    // Source input for respective EXTI 
    // Specify the AFIO_EXTICR register index [EXTICR1: 0-3 pin, EXTICR2: 4-7, EXTICR3: 8-11, EXTICR4: 12-15]
    //                               in array EXTICR[0]; EXTICR[1]; EXTICR[2]; EXTICR[3]; 
    index = pGPIO_PinConf.GPIO_PinNumber / 4;
    // Specify the bit position in the EXTICR register
    bit_pos = (pGPIO_PinConf.GPIO_PinNumber % 4) * 4;
    // Ex: PA10 -> index = 2 (AFIO_EXTICR3 = EXTICR[2]), bit_pos = 8 (shift 8-bits to EXTI10 of AFIO_EXTICR3), value = 0b0000

    // Specify the GPIO port
    port_code = AFIO_EXTICR_POTCODE(pGPIOx);
    AFIO->EXTICR[index] &= ~(0x0FU << bit_pos);     // Clear the 4 bits first
    AFIO->EXTICR[index] |= (port_code << bit_pos);  // Set the port code

    /* Configure the EXTI (interrupt mask, rising trigger, falling trigger, etc.) */
    // Select the edge trigger 
    switch (pGPIO_PinConf.GPIO_EdgeTrigger)
    {
        case GPIO_IT_EDGE_FT:
            EXTI->RTSR &= ~(0x01U << pGPIO_PinConf.GPIO_PinNumber);     // Clear or disable the rising trigger selcection
            EXTI->FTSR |= (0x01U << pGPIO_PinConf.GPIO_PinNumber);      // Set or enable the falling trigger selcection
            break;
        
        case GPIO_IT_EDGE_RT:
            EXTI->FTSR &= ~(0x01U << pGPIO_PinConf.GPIO_PinNumber);     // Clear or disable the falling trigger selcection
            EXTI->RTSR |= (0x01U << pGPIO_PinConf.GPIO_PinNumber);      // Set or enable the rising trigger selcection
            break;
        
        case GPIO_IT_EDGE_RFT:
            EXTI->FTSR |= (0x01U << pGPIO_PinConf.GPIO_PinNumber);
            EXTI->RTSR |= (0x01U << pGPIO_PinConf.GPIO_PinNumber);
            break;

        default:
            // Default GPIO_IT_EDGE_RFT
            EXTI->FTSR |= (0x01U << pGPIO_PinConf.GPIO_PinNumber);
            EXTI->RTSR |= (0x01U << pGPIO_PinConf.GPIO_PinNumber);
            break;
    }

    // Enable the interrupt/event mask
    // Masked (disabled), Unmasked (enabled)
    EXTI->IMR |= (0x01U << pGPIO_PinConf.GPIO_PinNumber);   // Set 1 because interrupt mask bus goes through OR logic gate

    /* Configure the NVIC (priority, enable IRQ) */
    // Set the priority
    NVIC_SetPriority(GPIO_PIN_TO_IRQ(pGPIO_PinConf.GPIO_PinNumber), IRQPriority);
    
    // Enable the IRQ
    NVIC_EnableIRQ(GPIO_PIN_TO_IRQ(pGPIO_PinConf.GPIO_PinNumber));
}