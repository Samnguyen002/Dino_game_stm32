#ifndef STM32F103XX_GPIO_DRIVER_H
#define STM32F103XX_GPIO_DRIVER_H
#include <stdint.h>
#include "stm32f103xx.h"

/* Ctrl + Alt + arrow down to select multiple lines */

/* GPIO pin configuration stuct*/
typedef struct 
{
    uint8_t GPIO_PinNumber;         /* The GPIO Pin to be configured: 16 pins */
    uint8_t GPIO_PinMode;           /* Specifies the operating mode of the selected pin with bit-field MODEy */
    uint8_t GPIO_PinConf;           /* Specifies the configuration bits with bit-field CNFy */
    uint8_t GPIO_PUPD;              /* Specifies the pull-up/pull-down activation of the input pin*/
    // Can add Alternate function, analog mode, floating input, etc.
    // Output Type: Push-pull, Open-drain, etc.
} GPIO_PinConf_t;

/* GPIO Pin state */
typedef enum
{
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET
} GPIO_PinState_t;

/* Can be used the bit-mask for definition: 0x0001, 0x0002, 0x004, etc. Bit-mask for assert: 0xffff */
/* GPIO_PinNumber */
#define GPIO_PIN_NUM_0        0U
#define GPIO_PIN_NUM_1        1U
#define GPIO_PIN_NUM_2        2U
#define GPIO_PIN_NUM_3        3U
#define GPIO_PIN_NUM_4        4U
#define GPIO_PIN_NUM_5        5U
#define GPIO_PIN_NUM_6        6U
#define GPIO_PIN_NUM_7        7U
#define GPIO_PIN_NUM_8        8U
#define GPIO_PIN_NUM_9        9U
#define GPIO_PIN_NUM_10       10U
#define GPIO_PIN_NUM_11       11U
#define GPIO_PIN_NUM_12       12U            
#define GPIO_PIN_NUM_13       13U
#define GPIO_PIN_NUM_14       14U
#define GPIO_PIN_NUM_15       15U

/* GPIO_PinMode */
#define GPIO_MODE_INPUT             0U    // Input Floating Mode: 0b00
#define GPIO_MODE_OUTPUT_MEDIUM     1U    // Output Max 10Mhz: 0b01
#define GPIO_MODE_OUTPUT_LOW        2U    // Output Max 2Mhz: 0b10
#define GPIO_MODE_OUTPUT_HIGH       3U    // Output Max 50Mhz: 0b11

/* GPIO_PinConf for Input Mode */
#define  GPIO_CNF_ANALOG             0u     /*!< 00: Analog mode  */
#define  GPIO_CNF_INPUT_FLOATING     1u     /*!< 01: Floating input (reset state)  */
#define  GPIO_CNF_INPUT_PU_PD        2u     /*!< 10: Input with pull-up / pull-down  */

/* GPIO_PinConf for Output Mode */
#define  GPIO_CNF_GP_OUTPUT_PP       0u     /*!< 00: General purpose output push-pull  */
#define  GPIO_CNF_GP_OUTPUT_OD       1u     /*!< 01: General purpose output Open-drain  */
#define  GPIO_CNF_AF_OUTPUT_PP       2u     /*!< 10: Alternate function output Push-pull  */
#define  GPIO_CNF_AF_OUTPUT_OD       3u     /*!< 11: Alternate function output Open-drain  */

/* GPIO_PUPD */
#define GPIO_NO_PUPD          0U
#define GPIO_PU               1U
#define GPIO_PD               2U

/* GPIO_ALFN */
// #define  GPIO_MODE_AF_INPUT                     GPIO_MODE_INPUT          /* Alternate Function Input Mode         */

/* GPIO_Init to initialize the GPIO pin configuration */
void GPIO_Init(GPIO_Reg_def_t *pGPIOx, GPIO_PinConf_t pGPIO_PinConf);

/* Write a value over GPIO_Pin */
void GPIO_WritePin(GPIO_Reg_def_t *pGPIOx, uint8_t PinNumber, GPIO_PinState_t GPIO_PinState);

/* Read a value from GPIO_Pin */
uint8_t GPIO_ReadPin(GPIO_Reg_def_t *pGPIOx, uint8_t PinNumber);

/* Toggle GPIO_Pin */
void GPIO_TogglePin(GPIO_Reg_def_t *pGPIOx, uint8_t PinNumber);

/* BSRR */
void GPIO_WritePinBit(GPIO_Reg_def_t *pGPIOx, uint8_t PinNumber, GPIO_PinState_t GPIO_PinState);

#endif
