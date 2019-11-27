/*******************************************************************************
* File Name: UARTBINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UARTB.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (UARTB_RX_INTERRUPT_ENABLED && (UARTB_RX_ENABLED || UARTB_HD_ENABLED))
    /*******************************************************************************
    * Function Name: UARTB_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UARTB_rxBuffer - RAM buffer pointer for save received data.
    *  UARTB_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  UARTB_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  UARTB_rxBufferOverflow - software overflow flag. Set to one
    *     when UARTB_rxBufferWrite index overtakes
    *     UARTB_rxBufferRead index.
    *  UARTB_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when UARTB_rxBufferWrite is equal to
    *    UARTB_rxBufferRead
    *  UARTB_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  UARTB_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(UARTB_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef UARTB_RXISR_ENTRY_CALLBACK
        UARTB_RXISR_EntryCallback();
    #endif /* UARTB_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START UARTB_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = UARTB_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in UARTB_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (UARTB_RX_STS_BREAK | 
                            UARTB_RX_STS_PAR_ERROR |
                            UARTB_RX_STS_STOP_ERROR | 
                            UARTB_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                UARTB_errorStatus |= readStatus & ( UARTB_RX_STS_BREAK | 
                                                            UARTB_RX_STS_PAR_ERROR | 
                                                            UARTB_RX_STS_STOP_ERROR | 
                                                            UARTB_RX_STS_OVERRUN);
                /* `#START UARTB_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef UARTB_RXISR_ERROR_CALLBACK
                UARTB_RXISR_ERROR_Callback();
            #endif /* UARTB_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & UARTB_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = UARTB_RXDATA_REG;
            #if (UARTB_RXHW_ADDRESS_ENABLED)
                if(UARTB_rxAddressMode == (uint8)UARTB__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & UARTB_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & UARTB_RX_STS_ADDR_MATCH) != 0u)
                        {
                            UARTB_rxAddressDetected = 1u;
                        }
                        else
                        {
                            UARTB_rxAddressDetected = 0u;
                        }
                    }
                    if(UARTB_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        UARTB_rxBuffer[UARTB_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    UARTB_rxBuffer[UARTB_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                UARTB_rxBuffer[UARTB_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (UARTB_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(UARTB_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        UARTB_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    UARTB_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(UARTB_rxBufferWrite >= UARTB_RX_BUFFER_SIZE)
                    {
                        UARTB_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(UARTB_rxBufferWrite == UARTB_rxBufferRead)
                    {
                        UARTB_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (UARTB_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            UARTB_RXSTATUS_MASK_REG  &= (uint8)~UARTB_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(UARTB_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (UARTB_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & UARTB_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START UARTB_RXISR_END` */

        /* `#END` */

    #ifdef UARTB_RXISR_EXIT_CALLBACK
        UARTB_RXISR_ExitCallback();
    #endif /* UARTB_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (UARTB_RX_INTERRUPT_ENABLED && (UARTB_RX_ENABLED || UARTB_HD_ENABLED)) */


#if (UARTB_TX_INTERRUPT_ENABLED && UARTB_TX_ENABLED)
    /*******************************************************************************
    * Function Name: UARTB_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UARTB_txBuffer - RAM buffer pointer for transmit data from.
    *  UARTB_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  UARTB_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(UARTB_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef UARTB_TXISR_ENTRY_CALLBACK
        UARTB_TXISR_EntryCallback();
    #endif /* UARTB_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START UARTB_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((UARTB_txBufferRead != UARTB_txBufferWrite) &&
             ((UARTB_TXSTATUS_REG & UARTB_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(UARTB_txBufferRead >= UARTB_TX_BUFFER_SIZE)
            {
                UARTB_txBufferRead = 0u;
            }

            UARTB_TXDATA_REG = UARTB_txBuffer[UARTB_txBufferRead];

            /* Set next pointer */
            UARTB_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UARTB_TXISR_END` */

        /* `#END` */

    #ifdef UARTB_TXISR_EXIT_CALLBACK
        UARTB_TXISR_ExitCallback();
    #endif /* UARTB_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (UARTB_TX_INTERRUPT_ENABLED && UARTB_TX_ENABLED) */


/* [] END OF FILE */
