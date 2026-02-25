#ifndef CORTEXM3_H
#define CORTEXM3_H
#include <stdint.h>

/* NVIC Register definition struct */
typedef struct NIVC
{
    volatile uint32_t ISER[3];          // Interrupt set-enable registes
             uint32_t RESERVED0[29];    // A gap between ISER block and IECR block (29 words (4bytes))
    volatile uint32_t ICER[3];          // Interrupt clear-enable registers
             uint32_t RESERVED0[29]; 
    volatile uint32_t ISPR[3];          // Interrupt set pending registers
             uint32_t RESERVED0[29]; 
    volatile uint32_t ICPR[3];          // Interrupt clear pending registers
             uint32_t RESERVED0[29]; 
    volatile uint32_t IABR[3];          // Interrupt active bit registers
             uint32_t RESERVED0[61]; 
    volatile uint32_t IPR[21];          // Interrupt priority registers (8-bit wide)
             uint32_t RESERVED0[683]; 
    volatile uint32_t STIR;             // Software trigger interrupt register
} NIVC_Reg_def_t;

/* Base address of the main NVIC register block */
#define NVIC    ((NIVC_Reg_def_t *)0xE000E100U)

/* Interrupt Request Number (IRQn) */
#define IRQ_NUM_EXTI0       6U
#define IRQ_NUM_EXTI1       7U
#define IRQ_NUM_EXTI2       8U
#define IRQ_NUM_EXTI3       9U
#define IRQ_NUM_EXTI4       10U
#define IRQ_NUM_EXTI9_5     23U
#define IRQ_NUM_EXTI15_10   40U

/* Each event is mapped to an IRQ number (positon), looks at the Interrupt block diagram */
/**
 * @brief This function enables interrupt request for the given IRQ
 * 
 * @param IRQNumber Interrupt request number to be set the priority
 */
void NVIC_EnableIRQ(uint8_t IRQNumber);

/**
 * @brief This function enables interrupt request for the given IRQ
 * 
 * @param IRQNumber Interrupt request number to be set the priority
 */
void NVIC_DisableIRQ(uint8_t IRQNumber);

/**
 * @brief This function sets the priority of the given IRQ number in the NVIC
 * 
 * @param IRQNumber Interrupt request number to be set the priority
 * @param IRQPriority The priority to be set, this should be the value in [0..16]
 *                    The NVIC priority register was written only in bits[7:4] of each bit field
 */
void NVIC_SetPriority(uint8_t IRQNumber, uint8_t IRQPriority);

#endif
