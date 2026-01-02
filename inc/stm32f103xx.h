#ifndef STM32F103XX_H
#define STM32F103XX_H

#include <stdint.h>

/* GPIO register defination struct */
typedef struct 
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_Reg_def_t;

/* RCC register definition struct */
typedef struct 
{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1NER;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t AHBSTR;
    volatile uint32_t CFGR2;
} RCC_Reg_def_t;


/* Define the pointer to indicate the base address of GPIO periperals*/
#define GPIOA ((GPIO_Reg_def_t *) 0x40010800UL)     // 0x40010800UL = (APB2_BASEADDR + 0x0800UL)
#define GPIOB ((GPIO_Reg_def_t *) 0x40010C00UL)     // 0x40010C00UL = (APB2_BASEADDR + 0x0C00UL)
#define GPIOC ((GPIO_Reg_def_t *) 0x40011000UL)
#define GPIOD ((GPIO_Reg_def_t *) 0x40011400UL)
#define GPIOE ((GPIO_Reg_def_t *) 0x40011800UL)
#define GPIOF ((GPIO_Reg_def_t *) 0x40011C00UL)
#define GPIOG ((GPIO_Reg_def_t *) 0x40012000UL)

/* Define the base address of the APB2 bus, it's the base address of AFIO peripheral
And you know, the base address of GPIO ports = APB2_BASEADDR + OFFSET (2 bytes last)*/
#define APB2_BASEADDR 0x40010000UL

/* Define AHB_BASEADDR */
#define AHB_BASEADDR 0x40018000UL

/* Define Reset and clock control base address */
#define RCC ((RCC_Reg_def_t *) AHB_BASEADDR + 0x9000UL)
// #define RCC ((RCC_Reg_def_t *) 0x40021000UL)

/* GPIO and Alternate function clock enable */
#define RCC_AFIO_CLK_EN()    (RCC->APB2ENR |= (0x01U << 0u))
#define RCC_GPIOA_CLK_EN()   (RCC->APB2ENR |= (0X01U << 2U))
#define RCC_GPIOB_CLK_EN()   (RCC->APB2ENR |= (0X01U << 3U))
#define RCC_GPIOC_CLK_EN()   (RCC->APB2ENR |= (0X01U << 4U))
#define RCC_GPIOD_CLK_EN()   (RCC->APB2ENR |= (0X01U << 5U))
#define RCC_GPIOE_CLK_EN()   (RCC->APB2ENR |= (0X01U << 6U))

/* GPIO and Alternate function clock disable */
#define RCC_AFIO_CLK_EN()    (RCC->APB2ENR &= ~(0x01U << 0u))
#define RCC_GPIOA_CLK_EN()   (RCC->APB2ENR &= ~(0X01U << 2U))
#define RCC_GPIOB_CLK_EN()   (RCC->APB2ENR &= ~(0X01U << 3U))
#define RCC_GPIOC_CLK_EN()   (RCC->APB2ENR &= ~(0X01U << 4U))
#define RCC_GPIOD_CLK_EN()   (RCC->APB2ENR &= ~(0X01U << 5U))
#define RCC_GPIOE_CLK_EN()   (RCC->APB2ENR &= ~(0X01U << 6U))

#include "stm32f103xx_gpio_driver.h"

#endif // STM32F103XX_h
