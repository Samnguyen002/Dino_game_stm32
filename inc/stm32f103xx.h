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
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t AHBSTR;
    volatile uint32_t CFGR2;
} RCC_Reg_def_t;

/* AFIO register definition struct */
typedef struct 
{
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;
    // volatile uint32_t EXTICR1;
    // volatile uint32_t EXTICR2;
    // volatile uint32_t EXTICR3
    // volatile uint32_t EXTICR4;
    volatile uint32_t EXTICR[4];
    volatile uint32_t MAPR2;
} AFIO_Reg_def_t;

/* EXTI register definition struct */
typedef struct 
{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_Reg_def_t;

/* USART register definition struct */
typedef struct
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_Reg_def_t;

/* Define the base address of the APB2 bus, it's the base address of AFIO peripheral
And you know, the base address of GPIO ports = APB2_BASEADDR + OFFSET (2 bytes last)*/
#define APB2_BASEADDR 0x40010000UL      

/* Define APB1_BASEADDR */
#define APB1_BASEADDR 0x40000000UL  

/* Define AHB_BASEADDR */
#define AHB_BASEADDR 0x40018000UL

/* Define the pointer to indicate the base address of GPIO periperals*/
#define GPIOA ((GPIO_Reg_def_t *) 0x40010800UL)     // 0x40010800UL = (APB2_BASEADDR + 0x0800UL)
#define GPIOB ((GPIO_Reg_def_t *) 0x40010C00UL)     // 0x40010C00UL = (APB2_BASEADDR + 0x0C00UL)
#define GPIOC ((GPIO_Reg_def_t *) 0x40011000UL)
#define GPIOD ((GPIO_Reg_def_t *) 0x40011400UL)
#define GPIOE ((GPIO_Reg_def_t *) 0x40011800UL)
#define GPIOF ((GPIO_Reg_def_t *) 0x40011C00UL)
#define GPIOG ((GPIO_Reg_def_t *) 0x40012000UL)

/* Define Reset and clock control base address */
#define RCC ((RCC_Reg_def_t *) AHB_BASEADDR + 0x9000UL)
// #define RCC ((RCC_Reg_def_t *) 0x40021000UL)

/* Define the AFIO peripheral base address */
#define AFIO ((AFIO_Reg_def_t *) (APB2_BASEADDR + 0x0000UL))

/* Define the EXTI peripgeral base address */
#define EXTI ((EXTI_Reg_def_t *) (APB2_BASEADDR + 0x0400UL))

/* Define USARTx peripheral base addesses */
#define USART1 ((USART_Reg_def_t *) (APB2_BASEADDR + 0x3800UL))
#define USART2 ((USART_Reg_def_t *) (APB1_BASEADDR + 0x4400UL))
#define USART3 ((USART_Reg_def_t *) (APB1_BASEADDR + 0x4800UL))
#define UART4  ((USART_Reg_def_t *) (APB1_BASEADDR + 0x4C00UL))
#define UART5  ((USART_Reg_def_t *) (APB1_BASEADDR + 0x5000UL))

/* GPIO and Alternate function clock enable */
#define RCC_AFIO_CLK_EN()    (RCC->APB2ENR |= (0x01U << 0u))
#define RCC_GPIOA_CLK_EN()   (RCC->APB2ENR |= (0X01U << 2U))
#define RCC_GPIOB_CLK_EN()   (RCC->APB2ENR |= (0X01U << 3U))
#define RCC_GPIOC_CLK_EN()   (RCC->APB2ENR |= (0X01U << 4U))
#define RCC_GPIOD_CLK_EN()   (RCC->APB2ENR |= (0X01U << 5U))
#define RCC_GPIOE_CLK_EN()   (RCC->APB2ENR |= (0X01U << 6U))
#define RCC_GPIOF_CLK_EN()   (RCC->APB2ENR |= (0X01U << 7U))
#define RCC_GPIOG_CLK_EN()   (RCC->APB2ENR |= (0X01U << 8U))

/* GPIO and Alternate function clock disable */
#define RCC_AFIO_CLK_DIS()    (RCC->APB2ENR &= ~(0x01U << 0u))
#define RCC_GPIOA_CLK_DIS()   (RCC->APB2ENR &= ~(0X01U << 2U))
#define RCC_GPIOB_CLK_DIS()   (RCC->APB2ENR &= ~(0X01U << 3U))
#define RCC_GPIOC_CLK_DIS()   (RCC->APB2ENR &= ~(0X01U << 4U))
#define RCC_GPIOD_CLK_DIS()   (RCC->APB2ENR &= ~(0X01U << 5U))
#define RCC_GPIOE_CLK_DIS()   (RCC->APB2ENR &= ~(0X01U << 6U))
#define RCC_GPIOF_CLK_DIS()   (RCC->APB2ENR &= ~(0X01U << 7U))
#define RCC_GPIOG_CLK_DIS()   (RCC->APB2ENR &= ~(0X01U << 8U))

/* USART function clock enable */
#define RCC_USART1_CLK_EN()    (RCC->APB2ENR |= (0x01U << 14u))
#define RCC_USART2_CLK_EN()    (RCC->APB1ENR |= (0x01U << 14u))
#define RCC_USART3_CLK_EN()    (RCC->APB1ENR |= (0x01U << 14u))
#define RCC_UART4_CLK_EN()     (RCC->APB1ENR |= (0x01U << 14u))
#define RCC_UART5_CLK_EN()     (RCC->APB1ENR |= (0x01U << 14u))

/* USART function clock disable */
#define RCC_USART1_CLK_DIS()    (RCC->APB2ENR &= ~(0x01U << 14u))
#define RCC_USART2_CLK_DIS()    (RCC->APB1ENR &= ~(0x01U << 14u))
#define RCC_USART3_CLK_DIS()    (RCC->APB1ENR &= ~(0x01U << 14u))
#define RCC_UART4_CLK_DIS()     (RCC->APB1ENR &= ~(0x01U << 14u))
#define RCC_UART5_CLK_DIS()     (RCC->APB1ENR &= ~(0x01U << 14u))

#include "stm32f103xx_gpio_driver.h"

#endif // STM32F103XX_h
