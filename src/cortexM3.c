#include "cortexM3.h"

void NVIC_SetPriority(uint8_t IRQNumber, uint8_t IRQPriority)
{
    uint8_t index;      /// Index of IPRx register
    uint8_t bit_pos;

    // IRQNumber = 6 (EXTI line 0) -> index = 1 -> IPR1 registers
    index = IRQNumber / 4U;

    // byte_pos = 6%4 = 2 (byte offset = 2) -> bits[23:16] of IPR1 responsible for EXTI0's piority
    // bit_pos = byte_pos * 8U
    bit_pos = (IRQNumber % 4) * 8U;

    // Set the priority
    NVIC->IPR[index] &= ~(0xFU << (bit_pos + 4));
    NVIC->IPR[index] |= (IRQPriority << (bit_pos + 4));   // Only bits[7:4] affects the priority
}

void NVIC_EnableIRQ(uint8_t IRQNumber)
{
    // IRQn[0-31]   -> ISER0, ICER0
    // IRQn[32-63]  -> ISER1, ICER1
    // IRQn[64-80]  -> ISER2, ICER2

    if (IRQNumber >= 0)
    {
        uint8_t index, bit_pos;
        index = IRQNumber / 32U;    // IRQNumber >> 5U
        bit_pos = IRQNumber % 32U;  // IRQNuber & 0x1FU (31=0001 1111)

        // Enable interrupt
        NVIC->ISER[index] |= (0x1U << bit_pos);

        /* NVIC->ISER[index] = (0x1U << bit_pos);  This's right because bit 0: no effect 
                                                   disable only by ICER register */
    }
}

void NVIC_DisableIRQ(uint8_t IRQNumber)
{
    if (IRQNumber >= 0)
    {
        NVIC->ICER[IRQNumber >> 5U] = (0x1U << (IRQNumber & 0x1FU));
    }
}
