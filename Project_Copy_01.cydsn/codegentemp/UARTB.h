/*******************************************************************************
* File Name: UARTB.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_UARTB_H)
#define CY_UART_UARTB_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define UARTB_RX_ENABLED                     (1u)
#define UARTB_TX_ENABLED                     (1u)
#define UARTB_HD_ENABLED                     (0u)
#define UARTB_RX_INTERRUPT_ENABLED           (0u)
#define UARTB_TX_INTERRUPT_ENABLED           (0u)
#define UARTB_INTERNAL_CLOCK_USED            (1u)
#define UARTB_RXHW_ADDRESS_ENABLED           (0u)
#define UARTB_OVER_SAMPLE_COUNT              (8u)
#define UARTB_PARITY_TYPE                    (0u)
#define UARTB_PARITY_TYPE_SW                 (0u)
#define UARTB_BREAK_DETECT                   (0u)
#define UARTB_BREAK_BITS_TX                  (13u)
#define UARTB_BREAK_BITS_RX                  (13u)
#define UARTB_TXCLKGEN_DP                    (1u)
#define UARTB_USE23POLLING                   (1u)
#define UARTB_FLOW_CONTROL                   (0u)
#define UARTB_CLK_FREQ                       (0u)
#define UARTB_TX_BUFFER_SIZE                 (4u)
#define UARTB_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(UARTB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define UARTB_CONTROL_REG_REMOVED            (0u)
#else
    #define UARTB_CONTROL_REG_REMOVED            (1u)
#endif /* End UARTB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct UARTB_backupStruct_
{
    uint8 enableState;

    #if(UARTB_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End UARTB_CONTROL_REG_REMOVED */

} UARTB_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void UARTB_Start(void) ;
void UARTB_Stop(void) ;
uint8 UARTB_ReadControlRegister(void) ;
void UARTB_WriteControlRegister(uint8 control) ;

void UARTB_Init(void) ;
void UARTB_Enable(void) ;
void UARTB_SaveConfig(void) ;
void UARTB_RestoreConfig(void) ;
void UARTB_Sleep(void) ;
void UARTB_Wakeup(void) ;

/* Only if RX is enabled */
#if( (UARTB_RX_ENABLED) || (UARTB_HD_ENABLED) )

    #if (UARTB_RX_INTERRUPT_ENABLED)
        #define UARTB_EnableRxInt()  CyIntEnable (UARTB_RX_VECT_NUM)
        #define UARTB_DisableRxInt() CyIntDisable(UARTB_RX_VECT_NUM)
        CY_ISR_PROTO(UARTB_RXISR);
    #endif /* UARTB_RX_INTERRUPT_ENABLED */

    void UARTB_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void UARTB_SetRxAddress1(uint8 address) ;
    void UARTB_SetRxAddress2(uint8 address) ;

    void  UARTB_SetRxInterruptMode(uint8 intSrc) ;
    uint8 UARTB_ReadRxData(void) ;
    uint8 UARTB_ReadRxStatus(void) ;
    uint8 UARTB_GetChar(void) ;
    uint16 UARTB_GetByte(void) ;
    uint8 UARTB_GetRxBufferSize(void)
                                                            ;
    void UARTB_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define UARTB_GetRxInterruptSource   UARTB_ReadRxStatus

#endif /* End (UARTB_RX_ENABLED) || (UARTB_HD_ENABLED) */

/* Only if TX is enabled */
#if(UARTB_TX_ENABLED || UARTB_HD_ENABLED)

    #if(UARTB_TX_INTERRUPT_ENABLED)
        #define UARTB_EnableTxInt()  CyIntEnable (UARTB_TX_VECT_NUM)
        #define UARTB_DisableTxInt() CyIntDisable(UARTB_TX_VECT_NUM)
        #define UARTB_SetPendingTxInt() CyIntSetPending(UARTB_TX_VECT_NUM)
        #define UARTB_ClearPendingTxInt() CyIntClearPending(UARTB_TX_VECT_NUM)
        CY_ISR_PROTO(UARTB_TXISR);
    #endif /* UARTB_TX_INTERRUPT_ENABLED */

    void UARTB_SetTxInterruptMode(uint8 intSrc) ;
    void UARTB_WriteTxData(uint8 txDataByte) ;
    uint8 UARTB_ReadTxStatus(void) ;
    void UARTB_PutChar(uint8 txDataByte) ;
    void UARTB_PutString(const char8 string[]) ;
    void UARTB_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void UARTB_PutCRLF(uint8 txDataByte) ;
    void UARTB_ClearTxBuffer(void) ;
    void UARTB_SetTxAddressMode(uint8 addressMode) ;
    void UARTB_SendBreak(uint8 retMode) ;
    uint8 UARTB_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define UARTB_PutStringConst         UARTB_PutString
    #define UARTB_PutArrayConst          UARTB_PutArray
    #define UARTB_GetTxInterruptSource   UARTB_ReadTxStatus

#endif /* End UARTB_TX_ENABLED || UARTB_HD_ENABLED */

#if(UARTB_HD_ENABLED)
    void UARTB_LoadRxConfig(void) ;
    void UARTB_LoadTxConfig(void) ;
#endif /* End UARTB_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UARTB) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    UARTB_CyBtldrCommStart(void) CYSMALL ;
    void    UARTB_CyBtldrCommStop(void) CYSMALL ;
    void    UARTB_CyBtldrCommReset(void) CYSMALL ;
    cystatus UARTB_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus UARTB_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UARTB)
        #define CyBtldrCommStart    UARTB_CyBtldrCommStart
        #define CyBtldrCommStop     UARTB_CyBtldrCommStop
        #define CyBtldrCommReset    UARTB_CyBtldrCommReset
        #define CyBtldrCommWrite    UARTB_CyBtldrCommWrite
        #define CyBtldrCommRead     UARTB_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UARTB) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define UARTB_BYTE2BYTE_TIME_OUT (25u)
    #define UARTB_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define UARTB_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define UARTB_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define UARTB_SET_SPACE      (0x00u)
#define UARTB_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (UARTB_TX_ENABLED) || (UARTB_HD_ENABLED) )
    #if(UARTB_TX_INTERRUPT_ENABLED)
        #define UARTB_TX_VECT_NUM            (uint8)UARTB_TXInternalInterrupt__INTC_NUMBER
        #define UARTB_TX_PRIOR_NUM           (uint8)UARTB_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UARTB_TX_INTERRUPT_ENABLED */

    #define UARTB_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define UARTB_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define UARTB_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(UARTB_TX_ENABLED)
        #define UARTB_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (UARTB_HD_ENABLED) */
        #define UARTB_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (UARTB_TX_ENABLED) */

    #define UARTB_TX_STS_COMPLETE            (uint8)(0x01u << UARTB_TX_STS_COMPLETE_SHIFT)
    #define UARTB_TX_STS_FIFO_EMPTY          (uint8)(0x01u << UARTB_TX_STS_FIFO_EMPTY_SHIFT)
    #define UARTB_TX_STS_FIFO_FULL           (uint8)(0x01u << UARTB_TX_STS_FIFO_FULL_SHIFT)
    #define UARTB_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << UARTB_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (UARTB_TX_ENABLED) || (UARTB_HD_ENABLED)*/

#if( (UARTB_RX_ENABLED) || (UARTB_HD_ENABLED) )
    #if(UARTB_RX_INTERRUPT_ENABLED)
        #define UARTB_RX_VECT_NUM            (uint8)UARTB_RXInternalInterrupt__INTC_NUMBER
        #define UARTB_RX_PRIOR_NUM           (uint8)UARTB_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UARTB_RX_INTERRUPT_ENABLED */
    #define UARTB_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define UARTB_RX_STS_BREAK_SHIFT             (0x01u)
    #define UARTB_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define UARTB_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define UARTB_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define UARTB_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define UARTB_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define UARTB_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define UARTB_RX_STS_MRKSPC           (uint8)(0x01u << UARTB_RX_STS_MRKSPC_SHIFT)
    #define UARTB_RX_STS_BREAK            (uint8)(0x01u << UARTB_RX_STS_BREAK_SHIFT)
    #define UARTB_RX_STS_PAR_ERROR        (uint8)(0x01u << UARTB_RX_STS_PAR_ERROR_SHIFT)
    #define UARTB_RX_STS_STOP_ERROR       (uint8)(0x01u << UARTB_RX_STS_STOP_ERROR_SHIFT)
    #define UARTB_RX_STS_OVERRUN          (uint8)(0x01u << UARTB_RX_STS_OVERRUN_SHIFT)
    #define UARTB_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << UARTB_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define UARTB_RX_STS_ADDR_MATCH       (uint8)(0x01u << UARTB_RX_STS_ADDR_MATCH_SHIFT)
    #define UARTB_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << UARTB_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define UARTB_RX_HW_MASK                     (0x7Fu)
#endif /* End (UARTB_RX_ENABLED) || (UARTB_HD_ENABLED) */

/* Control Register definitions */
#define UARTB_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define UARTB_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define UARTB_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define UARTB_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define UARTB_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define UARTB_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define UARTB_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define UARTB_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define UARTB_CTRL_HD_SEND               (uint8)(0x01u << UARTB_CTRL_HD_SEND_SHIFT)
#define UARTB_CTRL_HD_SEND_BREAK         (uint8)(0x01u << UARTB_CTRL_HD_SEND_BREAK_SHIFT)
#define UARTB_CTRL_MARK                  (uint8)(0x01u << UARTB_CTRL_MARK_SHIFT)
#define UARTB_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << UARTB_CTRL_PARITY_TYPE0_SHIFT)
#define UARTB_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << UARTB_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define UARTB_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define UARTB_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define UARTB_SEND_BREAK                         (0x00u)
#define UARTB_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define UARTB_REINIT                             (0x02u)
#define UARTB_SEND_WAIT_REINIT                   (0x03u)

#define UARTB_OVER_SAMPLE_8                      (8u)
#define UARTB_OVER_SAMPLE_16                     (16u)

#define UARTB_BIT_CENTER                         (UARTB_OVER_SAMPLE_COUNT - 2u)

#define UARTB_FIFO_LENGTH                        (4u)
#define UARTB_NUMBER_OF_START_BIT                (1u)
#define UARTB_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define UARTB_TXBITCTR_BREAKBITS8X   ((UARTB_BREAK_BITS_TX * UARTB_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define UARTB_TXBITCTR_BREAKBITS ((UARTB_BREAK_BITS_TX * UARTB_OVER_SAMPLE_COUNT) - 1u)

#define UARTB_HALF_BIT_COUNT   \
                            (((UARTB_OVER_SAMPLE_COUNT / 2u) + (UARTB_USE23POLLING * 1u)) - 2u)
#if (UARTB_OVER_SAMPLE_COUNT == UARTB_OVER_SAMPLE_8)
    #define UARTB_HD_TXBITCTR_INIT   (((UARTB_BREAK_BITS_TX + \
                            UARTB_NUMBER_OF_START_BIT) * UARTB_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define UARTB_RXBITCTR_INIT  ((((UARTB_BREAK_BITS_RX + UARTB_NUMBER_OF_START_BIT) \
                            * UARTB_OVER_SAMPLE_COUNT) + UARTB_HALF_BIT_COUNT) - 1u)

#else /* UARTB_OVER_SAMPLE_COUNT == UARTB_OVER_SAMPLE_16 */
    #define UARTB_HD_TXBITCTR_INIT   ((8u * UARTB_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define UARTB_RXBITCTR_INIT      (((7u * UARTB_OVER_SAMPLE_COUNT) - 1u) + \
                                                      UARTB_HALF_BIT_COUNT)
#endif /* End UARTB_OVER_SAMPLE_COUNT */

#define UARTB_HD_RXBITCTR_INIT                   UARTB_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 UARTB_initVar;
#if (UARTB_TX_INTERRUPT_ENABLED && UARTB_TX_ENABLED)
    extern volatile uint8 UARTB_txBuffer[UARTB_TX_BUFFER_SIZE];
    extern volatile uint8 UARTB_txBufferRead;
    extern uint8 UARTB_txBufferWrite;
#endif /* (UARTB_TX_INTERRUPT_ENABLED && UARTB_TX_ENABLED) */
#if (UARTB_RX_INTERRUPT_ENABLED && (UARTB_RX_ENABLED || UARTB_HD_ENABLED))
    extern uint8 UARTB_errorStatus;
    extern volatile uint8 UARTB_rxBuffer[UARTB_RX_BUFFER_SIZE];
    extern volatile uint8 UARTB_rxBufferRead;
    extern volatile uint8 UARTB_rxBufferWrite;
    extern volatile uint8 UARTB_rxBufferLoopDetect;
    extern volatile uint8 UARTB_rxBufferOverflow;
    #if (UARTB_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 UARTB_rxAddressMode;
        extern volatile uint8 UARTB_rxAddressDetected;
    #endif /* (UARTB_RXHW_ADDRESS_ENABLED) */
#endif /* (UARTB_RX_INTERRUPT_ENABLED && (UARTB_RX_ENABLED || UARTB_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define UARTB__B_UART__AM_SW_BYTE_BYTE 1
#define UARTB__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UARTB__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UARTB__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UARTB__B_UART__AM_NONE 0

#define UARTB__B_UART__NONE_REVB 0
#define UARTB__B_UART__EVEN_REVB 1
#define UARTB__B_UART__ODD_REVB 2
#define UARTB__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define UARTB_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define UARTB_NUMBER_OF_STOP_BITS    (1u)

#if (UARTB_RXHW_ADDRESS_ENABLED)
    #define UARTB_RX_ADDRESS_MODE    (0u)
    #define UARTB_RX_HW_ADDRESS1     (0u)
    #define UARTB_RX_HW_ADDRESS2     (0u)
#endif /* (UARTB_RXHW_ADDRESS_ENABLED) */

#define UARTB_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << UARTB_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << UARTB_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << UARTB_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << UARTB_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << UARTB_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << UARTB_RX_STS_BREAK_SHIFT) \
                                        | (0 << UARTB_RX_STS_OVERRUN_SHIFT))

#define UARTB_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << UARTB_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << UARTB_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << UARTB_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << UARTB_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef UARTB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UARTB_CONTROL_REG \
                            (* (reg8 *) UARTB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define UARTB_CONTROL_PTR \
                            (  (reg8 *) UARTB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End UARTB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UARTB_TX_ENABLED)
    #define UARTB_TXDATA_REG          (* (reg8 *) UARTB_BUART_sTX_TxShifter_u0__F0_REG)
    #define UARTB_TXDATA_PTR          (  (reg8 *) UARTB_BUART_sTX_TxShifter_u0__F0_REG)
    #define UARTB_TXDATA_AUX_CTL_REG  (* (reg8 *) UARTB_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UARTB_TXDATA_AUX_CTL_PTR  (  (reg8 *) UARTB_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UARTB_TXSTATUS_REG        (* (reg8 *) UARTB_BUART_sTX_TxSts__STATUS_REG)
    #define UARTB_TXSTATUS_PTR        (  (reg8 *) UARTB_BUART_sTX_TxSts__STATUS_REG)
    #define UARTB_TXSTATUS_MASK_REG   (* (reg8 *) UARTB_BUART_sTX_TxSts__MASK_REG)
    #define UARTB_TXSTATUS_MASK_PTR   (  (reg8 *) UARTB_BUART_sTX_TxSts__MASK_REG)
    #define UARTB_TXSTATUS_ACTL_REG   (* (reg8 *) UARTB_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define UARTB_TXSTATUS_ACTL_PTR   (  (reg8 *) UARTB_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(UARTB_TXCLKGEN_DP)
        #define UARTB_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) UARTB_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UARTB_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) UARTB_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UARTB_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) UARTB_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define UARTB_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) UARTB_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define UARTB_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) UARTB_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UARTB_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) UARTB_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UARTB_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UARTB_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UARTB_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UARTB_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UARTB_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) UARTB_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define UARTB_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) UARTB_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* UARTB_TXCLKGEN_DP */

#endif /* End UARTB_TX_ENABLED */

#if(UARTB_HD_ENABLED)

    #define UARTB_TXDATA_REG             (* (reg8 *) UARTB_BUART_sRX_RxShifter_u0__F1_REG )
    #define UARTB_TXDATA_PTR             (  (reg8 *) UARTB_BUART_sRX_RxShifter_u0__F1_REG )
    #define UARTB_TXDATA_AUX_CTL_REG     (* (reg8 *) UARTB_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define UARTB_TXDATA_AUX_CTL_PTR     (  (reg8 *) UARTB_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UARTB_TXSTATUS_REG           (* (reg8 *) UARTB_BUART_sRX_RxSts__STATUS_REG )
    #define UARTB_TXSTATUS_PTR           (  (reg8 *) UARTB_BUART_sRX_RxSts__STATUS_REG )
    #define UARTB_TXSTATUS_MASK_REG      (* (reg8 *) UARTB_BUART_sRX_RxSts__MASK_REG )
    #define UARTB_TXSTATUS_MASK_PTR      (  (reg8 *) UARTB_BUART_sRX_RxSts__MASK_REG )
    #define UARTB_TXSTATUS_ACTL_REG      (* (reg8 *) UARTB_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UARTB_TXSTATUS_ACTL_PTR      (  (reg8 *) UARTB_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End UARTB_HD_ENABLED */

#if( (UARTB_RX_ENABLED) || (UARTB_HD_ENABLED) )
    #define UARTB_RXDATA_REG             (* (reg8 *) UARTB_BUART_sRX_RxShifter_u0__F0_REG )
    #define UARTB_RXDATA_PTR             (  (reg8 *) UARTB_BUART_sRX_RxShifter_u0__F0_REG )
    #define UARTB_RXADDRESS1_REG         (* (reg8 *) UARTB_BUART_sRX_RxShifter_u0__D0_REG )
    #define UARTB_RXADDRESS1_PTR         (  (reg8 *) UARTB_BUART_sRX_RxShifter_u0__D0_REG )
    #define UARTB_RXADDRESS2_REG         (* (reg8 *) UARTB_BUART_sRX_RxShifter_u0__D1_REG )
    #define UARTB_RXADDRESS2_PTR         (  (reg8 *) UARTB_BUART_sRX_RxShifter_u0__D1_REG )
    #define UARTB_RXDATA_AUX_CTL_REG     (* (reg8 *) UARTB_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UARTB_RXBITCTR_PERIOD_REG    (* (reg8 *) UARTB_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UARTB_RXBITCTR_PERIOD_PTR    (  (reg8 *) UARTB_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UARTB_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UARTB_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UARTB_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UARTB_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UARTB_RXBITCTR_COUNTER_REG   (* (reg8 *) UARTB_BUART_sRX_RxBitCounter__COUNT_REG )
    #define UARTB_RXBITCTR_COUNTER_PTR   (  (reg8 *) UARTB_BUART_sRX_RxBitCounter__COUNT_REG )

    #define UARTB_RXSTATUS_REG           (* (reg8 *) UARTB_BUART_sRX_RxSts__STATUS_REG )
    #define UARTB_RXSTATUS_PTR           (  (reg8 *) UARTB_BUART_sRX_RxSts__STATUS_REG )
    #define UARTB_RXSTATUS_MASK_REG      (* (reg8 *) UARTB_BUART_sRX_RxSts__MASK_REG )
    #define UARTB_RXSTATUS_MASK_PTR      (  (reg8 *) UARTB_BUART_sRX_RxSts__MASK_REG )
    #define UARTB_RXSTATUS_ACTL_REG      (* (reg8 *) UARTB_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UARTB_RXSTATUS_ACTL_PTR      (  (reg8 *) UARTB_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (UARTB_RX_ENABLED) || (UARTB_HD_ENABLED) */

#if(UARTB_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define UARTB_INTCLOCK_CLKEN_REG     (* (reg8 *) UARTB_IntClock__PM_ACT_CFG)
    #define UARTB_INTCLOCK_CLKEN_PTR     (  (reg8 *) UARTB_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define UARTB_INTCLOCK_CLKEN_MASK    UARTB_IntClock__PM_ACT_MSK
#endif /* End UARTB_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(UARTB_TX_ENABLED)
    #define UARTB_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End UARTB_TX_ENABLED */

#if(UARTB_HD_ENABLED)
    #define UARTB_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End UARTB_HD_ENABLED */

#if( (UARTB_RX_ENABLED) || (UARTB_HD_ENABLED) )
    #define UARTB_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (UARTB_RX_ENABLED) || (UARTB_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define UARTB_WAIT_1_MS      UARTB_BL_CHK_DELAY_MS   

#define UARTB_TXBUFFERSIZE   UARTB_TX_BUFFER_SIZE
#define UARTB_RXBUFFERSIZE   UARTB_RX_BUFFER_SIZE

#if (UARTB_RXHW_ADDRESS_ENABLED)
    #define UARTB_RXADDRESSMODE  UARTB_RX_ADDRESS_MODE
    #define UARTB_RXHWADDRESS1   UARTB_RX_HW_ADDRESS1
    #define UARTB_RXHWADDRESS2   UARTB_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define UARTB_RXAddressMode  UARTB_RXADDRESSMODE
#endif /* (UARTB_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define UARTB_initvar                    UARTB_initVar

#define UARTB_RX_Enabled                 UARTB_RX_ENABLED
#define UARTB_TX_Enabled                 UARTB_TX_ENABLED
#define UARTB_HD_Enabled                 UARTB_HD_ENABLED
#define UARTB_RX_IntInterruptEnabled     UARTB_RX_INTERRUPT_ENABLED
#define UARTB_TX_IntInterruptEnabled     UARTB_TX_INTERRUPT_ENABLED
#define UARTB_InternalClockUsed          UARTB_INTERNAL_CLOCK_USED
#define UARTB_RXHW_Address_Enabled       UARTB_RXHW_ADDRESS_ENABLED
#define UARTB_OverSampleCount            UARTB_OVER_SAMPLE_COUNT
#define UARTB_ParityType                 UARTB_PARITY_TYPE

#if( UARTB_TX_ENABLED && (UARTB_TXBUFFERSIZE > UARTB_FIFO_LENGTH))
    #define UARTB_TXBUFFER               UARTB_txBuffer
    #define UARTB_TXBUFFERREAD           UARTB_txBufferRead
    #define UARTB_TXBUFFERWRITE          UARTB_txBufferWrite
#endif /* End UARTB_TX_ENABLED */
#if( ( UARTB_RX_ENABLED || UARTB_HD_ENABLED ) && \
     (UARTB_RXBUFFERSIZE > UARTB_FIFO_LENGTH) )
    #define UARTB_RXBUFFER               UARTB_rxBuffer
    #define UARTB_RXBUFFERREAD           UARTB_rxBufferRead
    #define UARTB_RXBUFFERWRITE          UARTB_rxBufferWrite
    #define UARTB_RXBUFFERLOOPDETECT     UARTB_rxBufferLoopDetect
    #define UARTB_RXBUFFER_OVERFLOW      UARTB_rxBufferOverflow
#endif /* End UARTB_RX_ENABLED */

#ifdef UARTB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UARTB_CONTROL                UARTB_CONTROL_REG
#endif /* End UARTB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UARTB_TX_ENABLED)
    #define UARTB_TXDATA                 UARTB_TXDATA_REG
    #define UARTB_TXSTATUS               UARTB_TXSTATUS_REG
    #define UARTB_TXSTATUS_MASK          UARTB_TXSTATUS_MASK_REG
    #define UARTB_TXSTATUS_ACTL          UARTB_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(UARTB_TXCLKGEN_DP)
        #define UARTB_TXBITCLKGEN_CTR        UARTB_TXBITCLKGEN_CTR_REG
        #define UARTB_TXBITCLKTX_COMPLETE    UARTB_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define UARTB_TXBITCTR_PERIOD        UARTB_TXBITCTR_PERIOD_REG
        #define UARTB_TXBITCTR_CONTROL       UARTB_TXBITCTR_CONTROL_REG
        #define UARTB_TXBITCTR_COUNTER       UARTB_TXBITCTR_COUNTER_REG
    #endif /* UARTB_TXCLKGEN_DP */
#endif /* End UARTB_TX_ENABLED */

#if(UARTB_HD_ENABLED)
    #define UARTB_TXDATA                 UARTB_TXDATA_REG
    #define UARTB_TXSTATUS               UARTB_TXSTATUS_REG
    #define UARTB_TXSTATUS_MASK          UARTB_TXSTATUS_MASK_REG
    #define UARTB_TXSTATUS_ACTL          UARTB_TXSTATUS_ACTL_REG
#endif /* End UARTB_HD_ENABLED */

#if( (UARTB_RX_ENABLED) || (UARTB_HD_ENABLED) )
    #define UARTB_RXDATA                 UARTB_RXDATA_REG
    #define UARTB_RXADDRESS1             UARTB_RXADDRESS1_REG
    #define UARTB_RXADDRESS2             UARTB_RXADDRESS2_REG
    #define UARTB_RXBITCTR_PERIOD        UARTB_RXBITCTR_PERIOD_REG
    #define UARTB_RXBITCTR_CONTROL       UARTB_RXBITCTR_CONTROL_REG
    #define UARTB_RXBITCTR_COUNTER       UARTB_RXBITCTR_COUNTER_REG
    #define UARTB_RXSTATUS               UARTB_RXSTATUS_REG
    #define UARTB_RXSTATUS_MASK          UARTB_RXSTATUS_MASK_REG
    #define UARTB_RXSTATUS_ACTL          UARTB_RXSTATUS_ACTL_REG
#endif /* End  (UARTB_RX_ENABLED) || (UARTB_HD_ENABLED) */

#if(UARTB_INTERNAL_CLOCK_USED)
    #define UARTB_INTCLOCK_CLKEN         UARTB_INTCLOCK_CLKEN_REG
#endif /* End UARTB_INTERNAL_CLOCK_USED */

#define UARTB_WAIT_FOR_COMLETE_REINIT    UARTB_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_UARTB_H */


/* [] END OF FILE */
