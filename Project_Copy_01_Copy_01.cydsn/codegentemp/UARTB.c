/*******************************************************************************
* File Name: UARTB.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UARTB.h"
#if (UARTB_INTERNAL_CLOCK_USED)
    #include "UARTB_IntClock.h"
#endif /* End UARTB_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 UARTB_initVar = 0u;

#if (UARTB_TX_INTERRUPT_ENABLED && UARTB_TX_ENABLED)
    volatile uint8 UARTB_txBuffer[UARTB_TX_BUFFER_SIZE];
    volatile uint8 UARTB_txBufferRead = 0u;
    uint8 UARTB_txBufferWrite = 0u;
#endif /* (UARTB_TX_INTERRUPT_ENABLED && UARTB_TX_ENABLED) */

#if (UARTB_RX_INTERRUPT_ENABLED && (UARTB_RX_ENABLED || UARTB_HD_ENABLED))
    uint8 UARTB_errorStatus = 0u;
    volatile uint8 UARTB_rxBuffer[UARTB_RX_BUFFER_SIZE];
    volatile uint8 UARTB_rxBufferRead  = 0u;
    volatile uint8 UARTB_rxBufferWrite = 0u;
    volatile uint8 UARTB_rxBufferLoopDetect = 0u;
    volatile uint8 UARTB_rxBufferOverflow   = 0u;
    #if (UARTB_RXHW_ADDRESS_ENABLED)
        volatile uint8 UARTB_rxAddressMode = UARTB_RX_ADDRESS_MODE;
        volatile uint8 UARTB_rxAddressDetected = 0u;
    #endif /* (UARTB_RXHW_ADDRESS_ENABLED) */
#endif /* (UARTB_RX_INTERRUPT_ENABLED && (UARTB_RX_ENABLED || UARTB_HD_ENABLED)) */


/*******************************************************************************
* Function Name: UARTB_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  UARTB_Start() sets the initVar variable, calls the
*  UARTB_Init() function, and then calls the
*  UARTB_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The UARTB_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time UARTB_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the UARTB_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UARTB_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(UARTB_initVar == 0u)
    {
        UARTB_Init();
        UARTB_initVar = 1u;
    }

    UARTB_Enable();
}


/*******************************************************************************
* Function Name: UARTB_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call UARTB_Init() because
*  the UARTB_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void UARTB_Init(void) 
{
    #if(UARTB_RX_ENABLED || UARTB_HD_ENABLED)

        #if (UARTB_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(UARTB_RX_VECT_NUM, &UARTB_RXISR);
            CyIntSetPriority(UARTB_RX_VECT_NUM, UARTB_RX_PRIOR_NUM);
            UARTB_errorStatus = 0u;
        #endif /* (UARTB_RX_INTERRUPT_ENABLED) */

        #if (UARTB_RXHW_ADDRESS_ENABLED)
            UARTB_SetRxAddressMode(UARTB_RX_ADDRESS_MODE);
            UARTB_SetRxAddress1(UARTB_RX_HW_ADDRESS1);
            UARTB_SetRxAddress2(UARTB_RX_HW_ADDRESS2);
        #endif /* End UARTB_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        UARTB_RXBITCTR_PERIOD_REG = UARTB_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        UARTB_RXSTATUS_MASK_REG  = UARTB_INIT_RX_INTERRUPTS_MASK;
    #endif /* End UARTB_RX_ENABLED || UARTB_HD_ENABLED*/

    #if(UARTB_TX_ENABLED)
        #if (UARTB_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(UARTB_TX_VECT_NUM, &UARTB_TXISR);
            CyIntSetPriority(UARTB_TX_VECT_NUM, UARTB_TX_PRIOR_NUM);
        #endif /* (UARTB_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (UARTB_TXCLKGEN_DP)
            UARTB_TXBITCLKGEN_CTR_REG = UARTB_BIT_CENTER;
            UARTB_TXBITCLKTX_COMPLETE_REG = ((UARTB_NUMBER_OF_DATA_BITS +
                        UARTB_NUMBER_OF_START_BIT) * UARTB_OVER_SAMPLE_COUNT) - 1u;
        #else
            UARTB_TXBITCTR_PERIOD_REG = ((UARTB_NUMBER_OF_DATA_BITS +
                        UARTB_NUMBER_OF_START_BIT) * UARTB_OVER_SAMPLE_8) - 1u;
        #endif /* End UARTB_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (UARTB_TX_INTERRUPT_ENABLED)
            UARTB_TXSTATUS_MASK_REG = UARTB_TX_STS_FIFO_EMPTY;
        #else
            UARTB_TXSTATUS_MASK_REG = UARTB_INIT_TX_INTERRUPTS_MASK;
        #endif /*End UARTB_TX_INTERRUPT_ENABLED*/

    #endif /* End UARTB_TX_ENABLED */

    #if(UARTB_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        UARTB_WriteControlRegister( \
            (UARTB_ReadControlRegister() & (uint8)~UARTB_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(UARTB_PARITY_TYPE << UARTB_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End UARTB_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: UARTB_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call UARTB_Enable() because the UARTB_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UARTB_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void UARTB_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (UARTB_RX_ENABLED || UARTB_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        UARTB_RXBITCTR_CONTROL_REG |= UARTB_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        UARTB_RXSTATUS_ACTL_REG  |= UARTB_INT_ENABLE;

        #if (UARTB_RX_INTERRUPT_ENABLED)
            UARTB_EnableRxInt();

            #if (UARTB_RXHW_ADDRESS_ENABLED)
                UARTB_rxAddressDetected = 0u;
            #endif /* (UARTB_RXHW_ADDRESS_ENABLED) */
        #endif /* (UARTB_RX_INTERRUPT_ENABLED) */
    #endif /* (UARTB_RX_ENABLED || UARTB_HD_ENABLED) */

    #if(UARTB_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!UARTB_TXCLKGEN_DP)
            UARTB_TXBITCTR_CONTROL_REG |= UARTB_CNTR_ENABLE;
        #endif /* End UARTB_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        UARTB_TXSTATUS_ACTL_REG |= UARTB_INT_ENABLE;
        #if (UARTB_TX_INTERRUPT_ENABLED)
            UARTB_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            UARTB_EnableTxInt();
        #endif /* (UARTB_TX_INTERRUPT_ENABLED) */
     #endif /* (UARTB_TX_INTERRUPT_ENABLED) */

    #if (UARTB_INTERNAL_CLOCK_USED)
        UARTB_IntClock_Start();  /* Enable the clock */
    #endif /* (UARTB_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UARTB_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void UARTB_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (UARTB_RX_ENABLED || UARTB_HD_ENABLED)
        UARTB_RXBITCTR_CONTROL_REG &= (uint8) ~UARTB_CNTR_ENABLE;
    #endif /* (UARTB_RX_ENABLED || UARTB_HD_ENABLED) */

    #if (UARTB_TX_ENABLED)
        #if(!UARTB_TXCLKGEN_DP)
            UARTB_TXBITCTR_CONTROL_REG &= (uint8) ~UARTB_CNTR_ENABLE;
        #endif /* (!UARTB_TXCLKGEN_DP) */
    #endif /* (UARTB_TX_ENABLED) */

    #if (UARTB_INTERNAL_CLOCK_USED)
        UARTB_IntClock_Stop();   /* Disable the clock */
    #endif /* (UARTB_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (UARTB_RX_ENABLED || UARTB_HD_ENABLED)
        UARTB_RXSTATUS_ACTL_REG  &= (uint8) ~UARTB_INT_ENABLE;

        #if (UARTB_RX_INTERRUPT_ENABLED)
            UARTB_DisableRxInt();
        #endif /* (UARTB_RX_INTERRUPT_ENABLED) */
    #endif /* (UARTB_RX_ENABLED || UARTB_HD_ENABLED) */

    #if (UARTB_TX_ENABLED)
        UARTB_TXSTATUS_ACTL_REG &= (uint8) ~UARTB_INT_ENABLE;

        #if (UARTB_TX_INTERRUPT_ENABLED)
            UARTB_DisableTxInt();
        #endif /* (UARTB_TX_INTERRUPT_ENABLED) */
    #endif /* (UARTB_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UARTB_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 UARTB_ReadControlRegister(void) 
{
    #if (UARTB_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(UARTB_CONTROL_REG);
    #endif /* (UARTB_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: UARTB_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  UARTB_WriteControlRegister(uint8 control) 
{
    #if (UARTB_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       UARTB_CONTROL_REG = control;
    #endif /* (UARTB_CONTROL_REG_REMOVED) */
}


#if(UARTB_RX_ENABLED || UARTB_HD_ENABLED)
    /*******************************************************************************
    * Function Name: UARTB_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      UARTB_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      UARTB_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      UARTB_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      UARTB_RX_STS_BREAK            Interrupt on break.
    *      UARTB_RX_STS_OVERRUN          Interrupt on overrun error.
    *      UARTB_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      UARTB_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void UARTB_SetRxInterruptMode(uint8 intSrc) 
    {
        UARTB_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: UARTB_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  UARTB_rxBuffer - RAM buffer pointer for save received data.
    *  UARTB_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  UARTB_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  UARTB_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 UARTB_ReadRxData(void) 
    {
        uint8 rxData;

    #if (UARTB_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        UARTB_DisableRxInt();

        locRxBufferRead  = UARTB_rxBufferRead;
        locRxBufferWrite = UARTB_rxBufferWrite;

        if( (UARTB_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = UARTB_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= UARTB_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            UARTB_rxBufferRead = locRxBufferRead;

            if(UARTB_rxBufferLoopDetect != 0u)
            {
                UARTB_rxBufferLoopDetect = 0u;
                #if ((UARTB_RX_INTERRUPT_ENABLED) && (UARTB_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( UARTB_HD_ENABLED )
                        if((UARTB_CONTROL_REG & UARTB_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            UARTB_RXSTATUS_MASK_REG  |= UARTB_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        UARTB_RXSTATUS_MASK_REG  |= UARTB_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end UARTB_HD_ENABLED */
                #endif /* ((UARTB_RX_INTERRUPT_ENABLED) && (UARTB_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = UARTB_RXDATA_REG;
        }

        UARTB_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = UARTB_RXDATA_REG;

    #endif /* (UARTB_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: UARTB_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  UARTB_RX_STS_FIFO_NOTEMPTY.
    *  UARTB_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  UARTB_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   UARTB_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   UARTB_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 UARTB_ReadRxStatus(void) 
    {
        uint8 status;

        status = UARTB_RXSTATUS_REG & UARTB_RX_HW_MASK;

    #if (UARTB_RX_INTERRUPT_ENABLED)
        if(UARTB_rxBufferOverflow != 0u)
        {
            status |= UARTB_RX_STS_SOFT_BUFF_OVER;
            UARTB_rxBufferOverflow = 0u;
        }
    #endif /* (UARTB_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: UARTB_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. UARTB_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  UARTB_rxBuffer - RAM buffer pointer for save received data.
    *  UARTB_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  UARTB_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  UARTB_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 UARTB_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (UARTB_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        UARTB_DisableRxInt();

        locRxBufferRead  = UARTB_rxBufferRead;
        locRxBufferWrite = UARTB_rxBufferWrite;

        if( (UARTB_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = UARTB_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= UARTB_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            UARTB_rxBufferRead = locRxBufferRead;

            if(UARTB_rxBufferLoopDetect != 0u)
            {
                UARTB_rxBufferLoopDetect = 0u;
                #if( (UARTB_RX_INTERRUPT_ENABLED) && (UARTB_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( UARTB_HD_ENABLED )
                        if((UARTB_CONTROL_REG & UARTB_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            UARTB_RXSTATUS_MASK_REG |= UARTB_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        UARTB_RXSTATUS_MASK_REG |= UARTB_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end UARTB_HD_ENABLED */
                #endif /* UARTB_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = UARTB_RXSTATUS_REG;
            if((rxStatus & UARTB_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = UARTB_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (UARTB_RX_STS_BREAK | UARTB_RX_STS_PAR_ERROR |
                                UARTB_RX_STS_STOP_ERROR | UARTB_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        UARTB_EnableRxInt();

    #else

        rxStatus =UARTB_RXSTATUS_REG;
        if((rxStatus & UARTB_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = UARTB_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (UARTB_RX_STS_BREAK | UARTB_RX_STS_PAR_ERROR |
                            UARTB_RX_STS_STOP_ERROR | UARTB_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (UARTB_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: UARTB_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 UARTB_GetByte(void) 
    {
        
    #if (UARTB_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        UARTB_DisableRxInt();
        locErrorStatus = (uint16)UARTB_errorStatus;
        UARTB_errorStatus = 0u;
        UARTB_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | UARTB_ReadRxData() );
    #else
        return ( ((uint16)UARTB_ReadRxStatus() << 8u) | UARTB_ReadRxData() );
    #endif /* UARTB_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: UARTB_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  UARTB_rxBufferWrite - used to calculate left bytes.
    *  UARTB_rxBufferRead - used to calculate left bytes.
    *  UARTB_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 UARTB_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (UARTB_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        UARTB_DisableRxInt();

        if(UARTB_rxBufferRead == UARTB_rxBufferWrite)
        {
            if(UARTB_rxBufferLoopDetect != 0u)
            {
                size = UARTB_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(UARTB_rxBufferRead < UARTB_rxBufferWrite)
        {
            size = (UARTB_rxBufferWrite - UARTB_rxBufferRead);
        }
        else
        {
            size = (UARTB_RX_BUFFER_SIZE - UARTB_rxBufferRead) + UARTB_rxBufferWrite;
        }

        UARTB_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((UARTB_RXSTATUS_REG & UARTB_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (UARTB_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: UARTB_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UARTB_rxBufferWrite - cleared to zero.
    *  UARTB_rxBufferRead - cleared to zero.
    *  UARTB_rxBufferLoopDetect - cleared to zero.
    *  UARTB_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void UARTB_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        UARTB_RXDATA_AUX_CTL_REG |= (uint8)  UARTB_RX_FIFO_CLR;
        UARTB_RXDATA_AUX_CTL_REG &= (uint8) ~UARTB_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (UARTB_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        UARTB_DisableRxInt();

        UARTB_rxBufferRead = 0u;
        UARTB_rxBufferWrite = 0u;
        UARTB_rxBufferLoopDetect = 0u;
        UARTB_rxBufferOverflow = 0u;

        UARTB_EnableRxInt();

    #endif /* (UARTB_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: UARTB_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  UARTB__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  UARTB__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  UARTB__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  UARTB__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  UARTB__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UARTB_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  UARTB_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void UARTB_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(UARTB_RXHW_ADDRESS_ENABLED)
            #if(UARTB_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* UARTB_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = UARTB_CONTROL_REG & (uint8)~UARTB_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << UARTB_CTRL_RXADDR_MODE0_SHIFT);
                UARTB_CONTROL_REG = tmpCtrl;

                #if(UARTB_RX_INTERRUPT_ENABLED && \
                   (UARTB_RXBUFFERSIZE > UARTB_FIFO_LENGTH) )
                    UARTB_rxAddressMode = addressMode;
                    UARTB_rxAddressDetected = 0u;
                #endif /* End UARTB_RXBUFFERSIZE > UARTB_FIFO_LENGTH*/
            #endif /* End UARTB_CONTROL_REG_REMOVED */
        #else /* UARTB_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End UARTB_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: UARTB_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void UARTB_SetRxAddress1(uint8 address) 
    {
        UARTB_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: UARTB_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void UARTB_SetRxAddress2(uint8 address) 
    {
        UARTB_RXADDRESS2_REG = address;
    }

#endif  /* UARTB_RX_ENABLED || UARTB_HD_ENABLED*/


#if( (UARTB_TX_ENABLED) || (UARTB_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: UARTB_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   UARTB_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   UARTB_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   UARTB_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   UARTB_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void UARTB_SetTxInterruptMode(uint8 intSrc) 
    {
        UARTB_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: UARTB_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  UARTB_txBuffer - RAM buffer pointer for save data for transmission
    *  UARTB_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  UARTB_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  UARTB_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UARTB_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(UARTB_initVar != 0u)
        {
        #if (UARTB_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            UARTB_DisableTxInt();

            if( (UARTB_txBufferRead == UARTB_txBufferWrite) &&
                ((UARTB_TXSTATUS_REG & UARTB_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                UARTB_TXDATA_REG = txDataByte;
            }
            else
            {
                if(UARTB_txBufferWrite >= UARTB_TX_BUFFER_SIZE)
                {
                    UARTB_txBufferWrite = 0u;
                }

                UARTB_txBuffer[UARTB_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                UARTB_txBufferWrite++;
            }

            UARTB_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            UARTB_TXDATA_REG = txDataByte;

        #endif /*(UARTB_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: UARTB_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 UARTB_ReadTxStatus(void) 
    {
        return(UARTB_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: UARTB_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UARTB_txBuffer - RAM buffer pointer for save data for transmission
    *  UARTB_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  UARTB_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  UARTB_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void UARTB_PutChar(uint8 txDataByte) 
    {
    #if (UARTB_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((UARTB_TX_BUFFER_SIZE > UARTB_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            UARTB_DisableTxInt();
        #endif /* (UARTB_TX_BUFFER_SIZE > UARTB_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = UARTB_txBufferWrite;
            locTxBufferRead  = UARTB_txBufferRead;

        #if ((UARTB_TX_BUFFER_SIZE > UARTB_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            UARTB_EnableTxInt();
        #endif /* (UARTB_TX_BUFFER_SIZE > UARTB_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(UARTB_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((UARTB_TXSTATUS_REG & UARTB_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            UARTB_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= UARTB_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            UARTB_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((UARTB_TX_BUFFER_SIZE > UARTB_MAX_BYTE_VALUE) && (CY_PSOC3))
            UARTB_DisableTxInt();
        #endif /* (UARTB_TX_BUFFER_SIZE > UARTB_MAX_BYTE_VALUE) && (CY_PSOC3) */

            UARTB_txBufferWrite = locTxBufferWrite;

        #if ((UARTB_TX_BUFFER_SIZE > UARTB_MAX_BYTE_VALUE) && (CY_PSOC3))
            UARTB_EnableTxInt();
        #endif /* (UARTB_TX_BUFFER_SIZE > UARTB_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (UARTB_TXSTATUS_REG & UARTB_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                UARTB_SetPendingTxInt();
            }
        }

    #else

        while((UARTB_TXSTATUS_REG & UARTB_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        UARTB_TXDATA_REG = txDataByte;

    #endif /* UARTB_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: UARTB_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UARTB_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void UARTB_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(UARTB_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                UARTB_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: UARTB_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UARTB_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void UARTB_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(UARTB_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                UARTB_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: UARTB_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UARTB_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UARTB_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(UARTB_initVar != 0u)
        {
            UARTB_PutChar(txDataByte);
            UARTB_PutChar(0x0Du);
            UARTB_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: UARTB_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not count.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  UARTB_txBufferWrite - used to calculate left space.
    *  UARTB_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 UARTB_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (UARTB_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        UARTB_DisableTxInt();

        if(UARTB_txBufferRead == UARTB_txBufferWrite)
        {
            size = 0u;
        }
        else if(UARTB_txBufferRead < UARTB_txBufferWrite)
        {
            size = (UARTB_txBufferWrite - UARTB_txBufferRead);
        }
        else
        {
            size = (UARTB_TX_BUFFER_SIZE - UARTB_txBufferRead) +
                    UARTB_txBufferWrite;
        }

        UARTB_EnableTxInt();

    #else

        size = UARTB_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & UARTB_TX_STS_FIFO_FULL) != 0u)
        {
            size = UARTB_FIFO_LENGTH;
        }
        else if((size & UARTB_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (UARTB_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: UARTB_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UARTB_txBufferWrite - cleared to zero.
    *  UARTB_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void UARTB_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        UARTB_TXDATA_AUX_CTL_REG |= (uint8)  UARTB_TX_FIFO_CLR;
        UARTB_TXDATA_AUX_CTL_REG &= (uint8) ~UARTB_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (UARTB_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        UARTB_DisableTxInt();

        UARTB_txBufferRead = 0u;
        UARTB_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        UARTB_EnableTxInt();

    #endif /* (UARTB_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: UARTB_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   UARTB_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   UARTB_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   UARTB_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   UARTB_SEND_WAIT_REINIT - Performs both options: 
    *      UARTB_SEND_BREAK and UARTB_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UARTB_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with UARTB_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The UARTB_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void UARTB_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(UARTB_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(UARTB_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == UARTB_SEND_BREAK) ||
                (retMode == UARTB_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                UARTB_WriteControlRegister(UARTB_ReadControlRegister() |
                                                      UARTB_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                UARTB_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = UARTB_TXSTATUS_REG;
                }
                while((tmpStat & UARTB_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == UARTB_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == UARTB_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = UARTB_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & UARTB_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == UARTB_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == UARTB_REINIT) ||
                (retMode == UARTB_SEND_WAIT_REINIT) )
            {
                UARTB_WriteControlRegister(UARTB_ReadControlRegister() &
                                              (uint8)~UARTB_CTRL_HD_SEND_BREAK);
            }

        #else /* UARTB_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == UARTB_SEND_BREAK) ||
                (retMode == UARTB_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (UARTB_PARITY_TYPE != UARTB__B_UART__NONE_REVB) || \
                                    (UARTB_PARITY_TYPE_SW != 0u) )
                    UARTB_WriteControlRegister(UARTB_ReadControlRegister() |
                                                          UARTB_CTRL_HD_SEND_BREAK);
                #endif /* End UARTB_PARITY_TYPE != UARTB__B_UART__NONE_REVB  */

                #if(UARTB_TXCLKGEN_DP)
                    txPeriod = UARTB_TXBITCLKTX_COMPLETE_REG;
                    UARTB_TXBITCLKTX_COMPLETE_REG = UARTB_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = UARTB_TXBITCTR_PERIOD_REG;
                    UARTB_TXBITCTR_PERIOD_REG = UARTB_TXBITCTR_BREAKBITS8X;
                #endif /* End UARTB_TXCLKGEN_DP */

                /* Send zeros */
                UARTB_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = UARTB_TXSTATUS_REG;
                }
                while((tmpStat & UARTB_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == UARTB_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == UARTB_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = UARTB_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & UARTB_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == UARTB_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == UARTB_REINIT) ||
                (retMode == UARTB_SEND_WAIT_REINIT) )
            {

            #if(UARTB_TXCLKGEN_DP)
                UARTB_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                UARTB_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End UARTB_TXCLKGEN_DP */

            #if( (UARTB_PARITY_TYPE != UARTB__B_UART__NONE_REVB) || \
                 (UARTB_PARITY_TYPE_SW != 0u) )
                UARTB_WriteControlRegister(UARTB_ReadControlRegister() &
                                                      (uint8) ~UARTB_CTRL_HD_SEND_BREAK);
            #endif /* End UARTB_PARITY_TYPE != NONE */
            }
        #endif    /* End UARTB_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: UARTB_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       UARTB_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       UARTB_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears UARTB_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void UARTB_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( UARTB_CONTROL_REG_REMOVED == 0u )
            UARTB_WriteControlRegister(UARTB_ReadControlRegister() |
                                                  UARTB_CTRL_MARK);
        #endif /* End UARTB_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( UARTB_CONTROL_REG_REMOVED == 0u )
            UARTB_WriteControlRegister(UARTB_ReadControlRegister() &
                                                  (uint8) ~UARTB_CTRL_MARK);
        #endif /* End UARTB_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndUARTB_TX_ENABLED */

#if(UARTB_HD_ENABLED)


    /*******************************************************************************
    * Function Name: UARTB_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void UARTB_LoadRxConfig(void) 
    {
        UARTB_WriteControlRegister(UARTB_ReadControlRegister() &
                                                (uint8)~UARTB_CTRL_HD_SEND);
        UARTB_RXBITCTR_PERIOD_REG = UARTB_HD_RXBITCTR_INIT;

    #if (UARTB_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        UARTB_SetRxInterruptMode(UARTB_INIT_RX_INTERRUPTS_MASK);
    #endif /* (UARTB_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: UARTB_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void UARTB_LoadTxConfig(void) 
    {
    #if (UARTB_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        UARTB_SetRxInterruptMode(0u);
    #endif /* (UARTB_RX_INTERRUPT_ENABLED) */

        UARTB_WriteControlRegister(UARTB_ReadControlRegister() | UARTB_CTRL_HD_SEND);
        UARTB_RXBITCTR_PERIOD_REG = UARTB_HD_TXBITCTR_INIT;
    }

#endif  /* UARTB_HD_ENABLED */


/* [] END OF FILE */
