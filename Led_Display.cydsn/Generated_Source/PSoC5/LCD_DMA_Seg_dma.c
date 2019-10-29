/***************************************************************************
* File Name: LCD_DMA_Seg_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <LCD_DMA_Seg_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* LCD_DMA_Seg__DRQ_CTL_REG
* 
* 
* LCD_DMA_Seg__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* LCD_DMA_Seg__NUMBEROF_TDS
* 
* Priority of this channel.
* LCD_DMA_Seg__PRIORITY
* 
* True if LCD_DMA_Seg_TERMIN_SEL is used.
* LCD_DMA_Seg__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* LCD_DMA_Seg__TERMIN_SEL
* 
* 
* True if LCD_DMA_Seg_TERMOUT0_SEL is used.
* LCD_DMA_Seg__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* LCD_DMA_Seg__TERMOUT0_SEL
* 
* 
* True if LCD_DMA_Seg_TERMOUT1_SEL is used.
* LCD_DMA_Seg__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* LCD_DMA_Seg__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of LCD_DMA_Seg dma channel */
uint8 LCD_DMA_Seg_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 LCD_DMA_Seg_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 LCD_DMA_Seg_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    LCD_DMA_Seg_DmaHandle = (uint8)LCD_DMA_Seg__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(LCD_DMA_Seg_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)LCD_DMA_Seg__TERMOUT0_SEL,
                                  (uint8)LCD_DMA_Seg__TERMOUT1_SEL,
                                  (uint8)LCD_DMA_Seg__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(LCD_DMA_Seg_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(LCD_DMA_Seg_DmaHandle, (uint8)LCD_DMA_Seg__PRIORITY);
    
    return LCD_DMA_Seg_DmaHandle;
}

/*********************************************************************
* Function Name: void LCD_DMA_Seg_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with LCD_DMA_Seg.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void LCD_DMA_Seg_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(LCD_DMA_Seg_DmaHandle);
}

