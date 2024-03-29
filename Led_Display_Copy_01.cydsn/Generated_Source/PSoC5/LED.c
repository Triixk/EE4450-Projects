/*******************************************************************************
* File Name: LED.c
* Version 1.10
*
* Description:
*  This file contains the setup, control and status commands for the 
*  LED Driver component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "LED.h"
#include <LED_DMA_Com_dma.h>
#include <LED_DMA_Seg_dma.h>
#if (LED_BRIGHTNESS_EN == LED_ENABLED)
    #include <LED_DMA_BC_dma.h>
#endif /* (LED_BRIGHTNESS_EN == LED_ENABLED) */

/* Function prototypes */
static void LED_DmaInit(void) ;
static void LED_DmaEnable(void) ;
static void LED_DmaDisable(void) ;

/* Used to hold the common line output sequence */
#if(LED_COM_DRIVE == LED_HIGH)
    static uint8 LED_comBuffer[16] = {0x00u, 0x01u, 0x00u, 0x02u, 0x00u, 0x04u, 0x00u, 0x08u,
                                                    0x00u, 0x10u, 0x00u, 0x20u, 0x00u, 0x40u, 0x00u, 0x80u};
#else
    static uint8 LED_comBuffer[16] = {0xFFu, 0xFEu, 0xFFu, 0xFDu, 0xFFu, 0xFBu, 0xFFu, 0xF7u,
                                                    0xFFu, 0xEFu, 0xFFu, 0xDFu, 0xFFu, 0xBFu, 0xFFu, 0x7Fu};
#endif /* (LED_COM_DRIVE == LED_HIGH) */

/* Buffers used to hold the display(segment) values to be transferred to the control registers */
uint8 LED_segLBuffer[LED_NUM_COM];
#if (LED_NUM_SEG > 8u) 
    uint8 LED_segMBuffer[LED_NUM_COM];
#endif /* (LED_NUM_SEG > 8u) */
#if (LED_NUM_SEG > 16u) 
    uint8 LED_segHBuffer[LED_NUM_COM];
#endif /* (LED_NUM_SEG > 16u) */

#if (LED_BRIGHTNESS_EN == LED_ENABLED)
    /* The brightness register used to hold the brightness levels for each common */
    static uint8 LED_brightnessReg[LED_NUM_COM];
#endif /* (LED_BRIGHTNESS_EN == LED_ENABLED) */

/* DMA channel and TD declaractions */
static uint8 LED_dmaComChannel;
static uint8 LED_dmaComTd[LED_TWO_NUM_COM];

static uint8 LED_dmaSegChannel;
static uint8 LED_dmaSegLTd[LED_NUM_COM];

#if (LED_BRIGHTNESS_EN == LED_ENABLED)
    static uint8 LED_dmaBCChannel;
    static uint8 LED_dmaBCTd;
#endif /* (LED_BRIGHTNESS_EN == LED_ENABLED) */

uint8 LED_initVar = 0u;
uint8 LED_enableVar = 0u;


/*******************************************************************************
* Function Name: LED_DmaInit
********************************************************************************
*
* Summary: 
*  Initializes the DMAs for transferring from the buffer register arrays to 
*  the control registers.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects: 
*  None
*
*******************************************************************************/
static void LED_DmaInit(void) 
{
    uint8  i;
    
    /* Segment TDs for Seg_Driver_M and Seg_Driver_H control registers */
    #if (LED_NUM_SEG > 8u)
        static uint8 LED_dmaSegMTd[LED_NUM_COM];
    #endif /* (LED_NUM_SEG > 8u) */
    #if (LED_NUM_SEG > 16u)
        static uint8 LED_dmaSegHTd[LED_NUM_COM];
    #endif /* (LED_NUM_SEG > 16u) */

    /************************* DMA configuration for the Commons *************************/
    /* Common DMA channel */
    LED_dmaComChannel = LED_DMA_Com_DmaInitialize(1u, 1u, 
                                        HI16(LED_SRAM_BASE), HI16(LED_CONTROL_REG_BASE));

    /* Check if the channel is valid */                                                                        
    if(LED_dmaComChannel != DMA_INVALID_CHANNEL)
    {
        /* Allocate the common TDs */
        for(i = 0u; i < LED_TWO_NUM_COM; i++)
        {
            LED_dmaComTd[i] = CyDmaTdAllocate();
        }
        
        /* Set configuration for the Common TDs */
        for(i = 0u;  i < (LED_TWO_NUM_COM - 1u); i++)
        {
            /* Separate configurations for odd and even TDs */
            if((uint8)(i & 1u) == 0u)
            {
                /* Set configuration for the Common TDs */
                (void) CyDmaTdSetConfiguration(LED_dmaComTd[i], 1u, 
                                                LED_dmaComTd[i+1u],
                                                TD_INC_SRC_ADR | LED_DMA_Com__TD_TERMOUT_EN);
            }
            else
            {
                /* Set configuration for the Common TDs */
                (void) CyDmaTdSetConfiguration(LED_dmaComTd[i], 1u,
                                                LED_dmaComTd[i+1u], TD_INC_SRC_ADR);
            }
        }
        /* Set the wraparound Common TD configuration */
        (void) CyDmaTdSetConfiguration(LED_dmaComTd[LED_TWO_NUM_COM - 1u], 
                                        1u, LED_dmaComTd[0u], TD_INC_SRC_ADR);
        
        /* Set the lower addresses of the common TDs */
        for(i = 0u; i < LED_TWO_NUM_COM; i++)
        {
            (void) CyDmaTdSetAddress(LED_dmaComTd[i],
                                        LO16((uint32) &LED_comBuffer[i]),
                                        LO16((uint32) LED_COM_CONTROL_PTR));
        }    
    }
    
    
    /*********************** DMA configuration for the Segments ***********************/
    /* Get the DMA channels for the segments */
    LED_dmaSegChannel = LED_DMA_Seg_DmaInitialize(1u, 1u, 
                                        HI16(LED_SRAM_BASE), HI16(LED_CONTROL_REG_BASE));
    
    /* Check if the segment channel is valid */
    if(LED_dmaSegChannel != DMA_INVALID_CHANNEL)
    {
        /* Allocate separate Tds for segments to implement the chain */
        for(i = 0u; i < LED_NUM_COM; i++)
        {
            LED_dmaSegLTd[i] = CyDmaTdAllocate();
            #if (LED_NUM_SEG > 8u)
                LED_dmaSegMTd[i] = CyDmaTdAllocate();
            #endif /* (LED_NUM_SEG > 8u) */
            #if (LED_NUM_SEG > 16u)
                LED_dmaSegHTd[i] = CyDmaTdAllocate();
            #endif /* (LED_NUM_SEG > 16u) */
        }
        
        /* Set the configuration for the Segment TDs */
        for(i = 0u; i < (LED_NUM_COM - 1u); i++)
        {
            #if (LED_NUM_SEG <= 8u)
                (void) CyDmaTdSetConfiguration(LED_dmaSegLTd[i], 1u, LED_dmaSegLTd[i+1u],
                                                TD_INC_SRC_ADR | LED_DMA_Seg__TD_TERMOUT_EN);
            #else    
                (void) CyDmaTdSetConfiguration(LED_dmaSegLTd[i], 1u, LED_dmaSegMTd[i],
                                                TD_INC_SRC_ADR | TD_AUTO_EXEC_NEXT);

                #if (LED_NUM_SEG <= 16u)
                    (void) CyDmaTdSetConfiguration(LED_dmaSegMTd[i], 1u, LED_dmaSegLTd[i+1u],
                                                    TD_INC_SRC_ADR | LED_DMA_Seg__TD_TERMOUT_EN);
                #else    
                    (void) CyDmaTdSetConfiguration(LED_dmaSegMTd[i], 1u, LED_dmaSegHTd[i],
                                                    TD_INC_SRC_ADR | TD_AUTO_EXEC_NEXT);
                    (void) CyDmaTdSetConfiguration(LED_dmaSegHTd[i], 1u, LED_dmaSegLTd[i+1u],
                                                    TD_INC_SRC_ADR | LED_DMA_Seg__TD_TERMOUT_EN);
                #endif /* LED_NUM_SEG <= 16u */
            #endif /* LED_NUM_SEG <= 8u */
        }
        
        /* Set the wraparound Segment TD configurations */
        #if (LED_NUM_SEG <= 8u)
            (void) CyDmaTdSetConfiguration(LED_dmaSegLTd[LED_NUM_COM - 1u],
                                            1u, LED_dmaSegLTd[0u], 
                                            TD_INC_SRC_ADR | LED_DMA_Seg__TD_TERMOUT_EN);
        #else    
            (void) CyDmaTdSetConfiguration(LED_dmaSegLTd[LED_NUM_COM - 1u],
                                            1u, LED_dmaSegMTd[LED_NUM_COM - 1u],
                                            TD_INC_SRC_ADR | TD_AUTO_EXEC_NEXT);
            #if (LED_NUM_SEG <= 16u)
                (void) CyDmaTdSetConfiguration(LED_dmaSegMTd[LED_NUM_COM - 1u],
                                                1u, LED_dmaSegLTd[0u], 
                                                TD_INC_SRC_ADR | LED_DMA_Seg__TD_TERMOUT_EN);
            #else    
                (void) CyDmaTdSetConfiguration(LED_dmaSegMTd[LED_NUM_COM - 1u],
                                                1u, LED_dmaSegHTd[LED_NUM_COM - 1u], 
                                                TD_INC_SRC_ADR | TD_AUTO_EXEC_NEXT);
                (void) CyDmaTdSetConfiguration(LED_dmaSegHTd[LED_NUM_COM - 1u],
                                                1u, LED_dmaSegLTd[0u], 
                                                TD_INC_SRC_ADR | LED_DMA_Seg__TD_TERMOUT_EN);
            #endif /* (LED_NUM_SEG <= 16u) */
        #endif /* (LED_NUM_SEG <= 8u) */
        
        /* The lower addresses for the segment TDs */
        for(i = 0u; i < LED_NUM_COM; i++)
        {
            (void) CyDmaTdSetAddress(LED_dmaSegLTd[i],
                                            LO16((uint32) &LED_segLBuffer[i]),
                                            LO16((uint32) LED_SEG_L_CONTROL_PTR));
            #if (LED_NUM_SEG > 8u)
                (void) CyDmaTdSetAddress(LED_dmaSegMTd[i],
                                            LO16((uint32) &LED_segMBuffer[i]),
                                            LO16((uint32) LED_SEG_M_CONTROL_PTR));
            #endif /* (LED_NUM_SEG > 8u) */
            #if (LED_NUM_SEG > 16u)
                (void) CyDmaTdSetAddress(LED_dmaSegHTd[i], 
                                            LO16((uint32) &LED_segHBuffer[i]),
                                            LO16((uint32) LED_SEG_H_CONTROL_PTR));
            #endif /* (LED_NUM_SEG > 16u) */
        }
    }
    
    
    /******************** DMA configuration for Brightness control *********************/
    
    #if (LED_BRIGHTNESS_EN == LED_ENABLED)
        /* Get the DMA channels */
        LED_dmaBCChannel = LED_DMA_BC_DmaInitialize(1u, 1u, 
                                        HI16(LED_SRAM_BASE), HI16(LED_CONTROL_REG_BASE));
            
        /* Check if the channels are valid */
        if(LED_dmaBCChannel != DMA_INVALID_CHANNEL)
        {
            LED_dmaBCTd = CyDmaTdAllocate();
            
            /* Set the TD configuration for the brightness DMA */
            (void) CyDmaTdSetConfiguration(LED_dmaBCTd, LED_NUM_COM,
                                        LED_dmaBCTd, TD_INC_SRC_ADR);
            
            /* Lower address for the brightness Td */
            (void) CyDmaTdSetAddress(LED_dmaBCTd, LO16((uint32) &LED_brightnessReg[0u]),
                                                               LO16((uint32)LED_COMPARE_PTR));
        }
    #endif /* (LED_BRIGHTNESS_EN == LED_ENABLED) */
}


/*******************************************************************************
* Function Name: LED_DmaEnable
********************************************************************************
*
* Summary: 
*  Enables the DMAs for transferring from the buffer register arrays to the
*  control registers.
*
* Parameters:
*  None
*
* Return: 
*  None
*
* Side Effects: 
*  None
*
*******************************************************************************/
static void LED_DmaEnable(void) 
{
    /* Initialize the TDs to the respective channels */
    (void) CyDmaChSetInitialTd(LED_dmaComChannel, LED_dmaComTd[0u]);
    (void) CyDmaChSetInitialTd(LED_dmaSegChannel, LED_dmaSegLTd[0u]);
    #if (LED_BRIGHTNESS_EN == LED_ENABLED)
        (void) CyDmaChSetInitialTd(LED_dmaBCChannel, LED_dmaBCTd);
    #endif /* (LED_BRIGHTNESS_EN == LED_ENABLED) */
    
    /* Enable all channels */
    (void) CyDmaChEnable(LED_dmaComChannel, 1u);
    (void) CyDmaChEnable(LED_dmaSegChannel, 1u);
    #if (LED_BRIGHTNESS_EN == LED_ENABLED)
        (void) CyDmaChEnable(LED_dmaBCChannel, 1u);
    #endif /* (LED_BRIGHTNESS_EN == LED_ENABLED) */
}


/*******************************************************************************
* Function Name: LED_DmaDisable
********************************************************************************
*
* Summary: 
*  Disables the DMAs for transferring from register array to the control 
*  register.
*
* Parameters:
*  None
*
* Return: 
*  None
*
* Side Effects: 
*  None
*
*******************************************************************************/
static void LED_DmaDisable(void) 
{
    uint8 i;
    uint8 channel;
    uint8 dmaChannelList[LED_CHANNEL_LIMIT];
    
    dmaChannelList[0u] = LED_dmaComChannel;
    dmaChannelList[1u] = LED_dmaSegChannel;
    #if (LED_BRIGHTNESS_EN == LED_ENABLED)
        dmaChannelList[2u] = LED_dmaBCChannel;
    #endif /* (LED_BRIGHTNESS_EN == LED_ENABLED) */

    for(i = 0u; i < LED_CHANNEL_LIMIT; i++)
    {
        channel = dmaChannelList[i];
        (void) CyDmaChDisable(channel);
        
        LED_Com_Driver_Write(LED_CLEAR);
        
        /* Clear any potential DMA requests and re-reset TD pointers */
        while(0u != (CY_DMA_CH_STRUCT_PTR[channel].basic_status[0u] & CY_DMA_STATUS_TD_ACTIVE))
        {
            ; /* Wait for to be cleared */
        }

        (void) CyDmaChSetRequest(channel, CY_DMA_CPU_TERM_CHAIN);
        (void) CyDmaChEnable    (channel, 1u);

        while(0u != (CY_DMA_CH_STRUCT_PTR[channel].basic_cfg[0u] & CY_DMA_STATUS_CHAIN_ACTIVE))
        {
            ; /* Wait for to be cleared */
        }
    }
}


/*******************************************************************************
* Function Name: LED_Init
********************************************************************************
*
* Summary: 
*  Performs initialization required for the component to operate.
*
* Parameters:
*  None
*
* Return: 
*  None
*
* Side Effects: 
*  This action clears the display.
*
*******************************************************************************/
void LED_Init(void) 
{
    static uint8 LED_dmaInitDone = 0u;
    #if (LED_BRIGHTNESS_EN == LED_ENABLED)
        uint8 i;
    #endif /* (LED_BRIGHTNESS_EN == LED_ENABLED) */
    
    /* Start fresh by clearing the display */
    LED_ClearDisplayAll();
    
    /* Initialize the DMAs */
    if(0u == LED_dmaInitDone)
    {
        LED_DmaInit();
        LED_dmaInitDone = 1u;
    }
    
    /* Set the brightness to full */
    #if (LED_BRIGHTNESS_EN == LED_ENABLED)
        for(i = 0u; i<(LED_NUM_COM); i++)
        {
            LED_brightnessReg[i] = LED_INIT_BRIGHT;
        }
    #endif /* (LED_BRIGHTNESS_EN == LED_ENABLED) */
}


/*******************************************************************************
* Function Name: LED_Enable
********************************************************************************
*
* Summary: 
*  Turns on the display.
*
* Parameters:
*  None
*
* Return: 
*  None
*
* Side Effects: 
*  None
*
*******************************************************************************/
void LED_Enable(void) 
{
    /* Enable the DMAs */
    LED_DmaEnable();
 
    #if (LED_BRIGHTNESS_EN == LED_ENABLED)
       /* Initialize to zero */
       LED_COUNTER_REG = 0x00u;
       LED_COMPARE_REG = 0x00u;
       
        /* Enable the PWM for brightness control */
       LED_CONTROL_REG = LED_CTRL_ENABLE;
    #endif /* (LED_BRIGHTNESS_EN == LED_ENABLED) */
    
    LED_enableVar = LED_CTRL_ENABLE;
}


/*******************************************************************************
* Function Name: LED_Start
********************************************************************************
*
* Summary:
*  Configures the hardware (DMA and optional PWM) and enables the LED
*  display. Whatever is currently in the display RAM will be displayed on the 
*  LED display. The display RAM is an array of 1 to 24 bytes called 
*  LED_Driver_1_SegmentRam[].
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side effects: 
*  None
*
*******************************************************************************/
void LED_Start(void) 
{
    if(0u == LED_initVar)
    {
        LED_Init();
        LED_initVar = 1u;
    }

    LED_Enable();
}


/*******************************************************************************
* Function Name: LED_Stop
********************************************************************************
*
* Summary:
*  Clears the display SRAM, disables all DMA channels and the stops the PWM
*  (if enabled in the customizer).
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Stop(void) 
{
    #if (LED_BRIGHTNESS_EN == LED_ENABLED)
        /* Disable the PWM */
        LED_CONTROL_REG = LED_CTRL_DISABLE;
    #endif /* (LED_BRIGHTNESS_EN == LED_ENABLED) */
    
    LED_DmaDisable();
    LED_ClearDisplayAll();
    
    LED_enableVar  = LED_CTRL_DISABLE;
}


/*******************************************************************************
* Function Name: LED_SetDisplayRAM
********************************************************************************
*
* Summary:
*  Writes 'value' directly into the display RAM. It is not necessary to use 
*  this API to manipulate the display RAM, you can also access the display 
*  RAM directly by writing to LED_segLBuffer,
*  LED_segMBuffer, LED_segHBuffer.
*
* Parameters:
*  uint8 value: Desired value to write into the display RAM. A '1' enables the
*               segment, a '0' disables the segment.
*  uint8 position: Position of the display that is modified.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_SetDisplayRAM(uint8 value, uint8 position) 
{
    uint8 relPosition;
    
    if(position < LED_NUM_COM)
    {
        relPosition = position;
        #if(LED_SEG_DRIVE == LED_HIGH)
            LED_segLBuffer[relPosition] = value;
        #else
            LED_segLBuffer[relPosition] = ((uint8) ~value);
        #endif /* LED_SEG_DRIVE == LED_HIGH */
    }    
    else if (position < LED_TWO_NUM_COM)
    {
        #if (LED_NUM_SEG > 8u)
            relPosition = position - LED_NUM_COM;
            #if(LED_SEG_DRIVE == LED_HIGH)
                LED_segMBuffer[relPosition] = value;
            #else
                LED_segMBuffer[relPosition] = ((uint8) ~value);
            #endif /* LED_SEG_DRIVE == LED_HIGH */
        #endif /* (LED_NUM_SEG > 8u) */
    }
    else
    {
        #if (LED_NUM_SEG > 16u)
            relPosition = position - LED_TWO_NUM_COM;
            if(relPosition < LED_NUM_COM)
            {
                #if(LED_SEG_DRIVE == LED_HIGH)
                    LED_segHBuffer[relPosition] = value;
                #else
                    LED_segMBuffer[relPosition] = ((uint8) ~value);
                #endif /* LED_SEG_DRIVE == LED_HIGH */
            }
        #endif /* (LED_NUM_SEG > 16u) */
    }
}


/*******************************************************************************
* Function Name: LED_SetRC
********************************************************************************
*
* Summary:
*  Sets the bit in the display RAM corresponding to the LED in the designated
*  row and column. Rows are the segments and columns are the commons.
*
* Parameters:
*  uint8 row: Row value 0 to 23.
*  uint8 col: Column between 0 and 7.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_SetRC(uint8 row, uint8 column) 
{
    uint8 rowSeg;
    
    if(column < LED_NUM_COM)
    {
        if(row < 8u)
        {
            rowSeg = row;
            #if(LED_SEG_DRIVE == LED_HIGH)
                LED_segLBuffer[column] |= ((uint8)((uint8)0x01u << rowSeg));
            #else
                LED_segLBuffer[column] &= ((uint8)~((uint8)((uint8)0x01u << rowSeg)));
            #endif /* LED_SEG_DRIVE == LED_HIGH */
        }
        else if (row < 16u)
        {
            #if (LED_NUM_SEG > 8u) 
                rowSeg = row - 8u;
                #if(LED_SEG_DRIVE == LED_HIGH)
                    LED_segMBuffer[column] |= ((uint8)((uint8)0x01u << rowSeg));
                #else
                    LED_segMBuffer[column] &= ((uint8)~((uint8)((uint8)0x01u << rowSeg)));
                #endif /* LED_SEG_DRIVE == LED_HIGH */
            #endif /* (LED_NUM_SEG > 8u) */
        }
        else
        {
            #if (LED_NUM_SEG > 16u)
                rowSeg = row - 16u;
                #if(LED_SEG_DRIVE == LED_HIGH)
                    LED_segHBuffer[column] |= ((uint8)((uint8)0x01u << rowSeg));
                #else
                    LED_segHBuffer[column] &= ((uint8)~((uint8)((uint8)0x01u << rowSeg)));
                #endif /* LED_SEG_DRIVE == LED_HIGH */
            #endif /* (LED_NUM_SEG > 16u) */
        }
    }
}


/*******************************************************************************
* Function Name: LED_ClearRC
********************************************************************************
*
* Summary:
*  Clears the bit in the display RAM corresponding to the LED in the designated
*  row and column.
*
* Parameters:
*  uint8 row: Row value 0 to 23.
*  uint8 col: Column between 0 and 7.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_ClearRC(uint8 row, uint8 column) 
{
    uint8 rowSeg;
    uint8 rowSelect;
    
    if(column < LED_NUM_COM)
    {
        if(row < 8u)
        {
            rowSeg = row;
            rowSelect = ((uint8)((uint8)0x01u << rowSeg));
            #if(LED_SEG_DRIVE == LED_HIGH)
                LED_segLBuffer[column] &= ((uint8)(~(uint8)rowSelect));
            #else
                LED_segLBuffer[column] |= rowSelect;
            #endif /* LED_SEG_DRIVE == LED_HIGH */
        }    
        else if (row < 16u)
        {
            #if (LED_NUM_SEG > 8u) 
                rowSeg = row - 8u;
                rowSelect = ((uint8)((uint8)0x01u << rowSeg));
                #if(LED_SEG_DRIVE == LED_HIGH)
                    LED_segMBuffer[column] &= ((uint8)(~(uint8)rowSelect));
                #else
                    LED_segMBuffer[column] |= rowSelect;
                #endif /* LED_SEG_DRIVE == LED_HIGH */
            #endif /* (LED_NUM_SEG > 8u) */
        }
        else
        {
            #if (LED_NUM_SEG > 16u)
                rowSeg = row - 16u;
                rowSelect = ((uint8)((uint8)0x01u << rowSeg));
                #if(LED_SEG_DRIVE == LED_HIGH)
                    LED_segHBuffer[column] &= ((uint8)(~(uint8)rowSelect));
                #else
                    LED_segHBuffer[column] |= rowSelect;
                #endif /* LED_SEG_DRIVE == LED_HIGH */
            #endif /* (LED_NUM_SEG > 16u) */
        }
    }
}


/*******************************************************************************
* Function Name: LED_ToggleRC
********************************************************************************
*
* Summary:
*  Toggles the bit in the display RAM corresponding to the LED in the designated
*  row and column.
*
* Parameters:
*  uint8 row: Row value 0 to 23.
*  uint8 col: Column between 0 and 7.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_ToggleRC(uint8 row, uint8 column) 
{
    uint8 rowSeg;
    
    if(column < LED_NUM_COM)
    {
        if(row < 8u)
        {
            rowSeg = row;
            LED_segLBuffer[column] ^= ((uint8)((uint8)0x01u << rowSeg));
        }    
        else if (row < 16u)
        {
            #if (LED_NUM_SEG > 8u)
                rowSeg = row - 8u;
                LED_segMBuffer[column] ^= ((uint8)((uint8)0x01u << rowSeg));
            #endif /* (LED_NUM_SEG > 8u) */
        } 
        else
        {
            #if (LED_NUM_SEG > 16u)
                rowSeg = row - 16u;
                LED_segHBuffer[column] ^= ((uint8)((uint8)0x01u << rowSeg));
            #endif /* (LED_NUM_SEG > 16u) */
        }
    }
}


/*******************************************************************************
* Function Name: LED_GetRC
********************************************************************************
*
* Summary:
*  Returns the bit value in the display RAM corresponding to the LED in the
*  designated row and column.
*
* Parameters:
*  uint8 row: Row value 0 to 23.
*  uint8 col: Column between 0 and 7.
*
* Return:
*  uint8 - bit value of the display RAM at the corresponding row and column. 
*
* Side effects:
*  None
*
*******************************************************************************/
uint8 LED_GetRC(uint8 row, uint8 column) 
{
    uint8 valueRC = 0u;
    uint8 rowSeg;
    uint8 rowSegSelect = 0u;
    
    if(column < LED_NUM_COM)
    {
        if(row < 8u)
        {
            rowSeg = row;
            rowSegSelect = (uint8)((uint8)LED_segLBuffer[column] >> rowSeg);
        }    
        else if (row < 16u)
        {
            #if (LED_NUM_SEG > 8u) 
                rowSeg = row - 8u;
                rowSegSelect = (uint8)((uint8)LED_segMBuffer[column] >> rowSeg);
            #endif /* (LED_NUM_SEG > 8u) */
        }
        else
        {
            #if (LED_NUM_SEG > 16u)
                rowSeg = row - 16u;
                rowSegSelect = (uint8)((uint8)LED_segHBuffer[column] >> rowSeg);
            #endif /* (LED_NUM_SEG > 16u) */
        }
        
        #if(LED_SEG_DRIVE == LED_HIGH)
            valueRC = (uint8)((uint8)rowSegSelect & 0x01u);
        #else
            valueRC = (uint8)((uint8)((uint8)~rowSegSelect) & 0x01u);
        #endif /* LED_SEG_DRIVE == LED_HIGH */
    }
    
    return(valueRC);
}


/*******************************************************************************
* Function Name: LED_ClearDisplay
********************************************************************************
*
* Summary:
*  Clears the display (disables all the LEDs) for the associated position by
*  setting the display RAM to zero.
*
* Parameters:
*  uint8 position: The digit position to clear.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_ClearDisplay(uint8 position) 
{  
    uint8 relPosition;
    
    if(position < LED_NUM_COM)
    {
        relPosition = position;
        LED_segLBuffer[relPosition] = LED_CLEAR;
    }    
    else if (position < LED_TWO_NUM_COM)
    {
        #if (LED_NUM_SEG > 8u)
            relPosition = position - LED_NUM_COM;
            LED_segMBuffer[relPosition] = LED_CLEAR;
        #endif /* (LED_NUM_SEG > 8u) */
    }
    else
    {
        #if (LED_NUM_SEG > 16u)
            relPosition = position - LED_TWO_NUM_COM;
            if(relPosition < LED_NUM_COM)
            {
                LED_segHBuffer[relPosition] = LED_CLEAR;
            }
        #endif /* (LED_NUM_SEG > 16u) */
    }
}


/*******************************************************************************
* Function Name: LED_ClearDisplayAll
********************************************************************************
*
* Summary:
*  Clears the entire display by writing zeros to all the display RAM locations.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_ClearDisplayAll(void) 
{
    uint8 position;
    
    for(position = 0u; position < LED_NUM_COM; position++)
    {
        LED_segLBuffer[position] = LED_CLEAR; 
        
        #if (LED_NUM_SEG > 8u) 
            LED_segMBuffer[position] = LED_CLEAR;
        #endif /* (LED_NUM_SEG > 8u) */
        
        #if (LED_NUM_SEG > 16u)
            LED_segHBuffer[position] = LED_CLEAR;
        #endif /* (LED_NUM_SEG > 16u) */
    }
}


/*******************************************************************************
* Function Name: LED_Write7SegNumberDec
********************************************************************************
*
* Summary:
*  Displays a signed integer up to 8 characters long, starting at 'position' 
*  and extending for 'digits' characters. The negative sign will consume one 
*  digit if it is required. If you do not use the correct number of digits for
*  your number, the least significant digits will be displayed. For example, 
*  if value is -1234, display is 0 and digits is 4, the result will be: -234.
*
* Parameters:
*  int32 number: a signed integer number to display. It is the responsibility 
*                of the user to ensure that the display has enough digits to 
*                accurately represent the number passed to this function. If 
*                not, the least significant digits will be displayed. Also note
*                that a negative number will require 1 more digit than the
*                equivalent positive number to display the negative sign.
*  uint8 position: Digit position of the Display/Common RAM to start.
*  uint8 digits: The number of digits you wish to use to display the value 
*                passed into the function. The negative sign will consume one 
*                digit if it is required.
*  uint8 alignment: How to align the provided number in the allocated digits.
*       RIGHT_ALIGN - Least significant digit occupies the rightmost digit
*                     (position + digits). Unused digits are turned off unless
*                     ZERO_PAD enabled.
*       LEFT_ALIGN - Most significant digit (or negative sign) occupies the
*                    digit specified by position. Unused digits are turned off.
*       ZERO_PAD - Unused digits to the left are padded with leading zeros.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Write7SegNumberDec(int32 number, uint8 position, uint8 digits, uint8 alignment)

{
    uint8 i;
    uint8 relPosition;
    uint8 choiceReg;
    uint8 numberSign;
    uint8 selectVal;
    uint8 zeroCount = 0u;
    uint8 bufArray[8u] = {0u};
    uint32 numberVal;
        
    /* Choose to use either the low, mid or high control registers */
    if(position < LED_NUM_COM)
    {
        choiceReg = LED_SEG_REG_LOW;
        relPosition = position;
    }
    else if (position < LED_TWO_NUM_COM)
    {
        choiceReg = LED_SEG_REG_MID;
        relPosition = position - LED_NUM_COM;
    }
    else
    {
        choiceReg = LED_SEG_REG_HIGH;
        relPosition = position - LED_TWO_NUM_COM;
    }
    
    /* Routine to extract the sign and to convert to unsigned */
    if(number >= LED_ZERO_NEG)
    {
        numberVal = (uint32)number;
        numberSign = LED_UNSIGNED;
    }
    else
    {
        numberVal = (uint32)(-number);
        numberSign = LED_SIGNED;
    }
    
    /* Fill up the temporary array */
    for(i = digits; i > 0u; i--)
    {
        selectVal = (uint8)(numberVal % 10u);
        bufArray[i-1u] = LED_EncodeNumber7Seg(selectVal);
        numberVal = numberVal / 10u;
    }
    
    /* Clean up the array and place sign if needed */
    if(alignment == LED_ZERO_PAD)
    {
        if(numberSign == LED_SIGNED)
        {
            /* Place sign on the MSB */
            bufArray[0u] = LED_EncodeChar7Seg('-');
        }
    }
    else
    {
        for(i = 0u; i < digits; i++)
        {
            if (bufArray[i] != LED_ZERO_7CHAR)
            {
                if(numberSign == LED_SIGNED)
                {
                    if(i == 0u)
                    {
                        /* Place sign on the MSB */
                        bufArray[i] = LED_EncodeChar7Seg('-');
                    }
                    else
                    {
                        /* Place sign before MSB */
                        bufArray[i-1u] = LED_EncodeChar7Seg('-');
                    }
                }
                /* Exit when encountering non-zero number */
                break;
            }
            else
            {
                if(zeroCount != (digits - 1u))
                {
                    /* Turn off the display */
                    bufArray[i] = LED_CLEAR;
                    zeroCount++;
                }
            }    
        }
    }
    
    /* Place the values in the segment array according to alignment */
    if(alignment == LED_LEFT_ALIGN)
    {
        for(i = 0u; i < digits; i++)
        {
            if(bufArray[i] != LED_CLEAR)
            {
                if(relPosition < LED_NUM_COM)
                {
                    /* Only show displays that are not empty */
                    switch(choiceReg)
                    {
                        case LED_SEG_REG_LOW :
                            LED_segLBuffer[relPosition] = bufArray[i];
                            break;
                        case LED_SEG_REG_MID :
                            #if (LED_NUM_SEG > 8u)
                                LED_segMBuffer[relPosition] = bufArray[i];
                            #endif /* (LED_NUM_SEG > 8u) */
                            break;
                        case LED_SEG_REG_HIGH :
                            #if (LED_NUM_SEG > 16u)
                                LED_segHBuffer[relPosition] = bufArray[i];
                            #endif /* (LED_NUM_SEG > 16u) */
                            break;
                        default :
                            LED_segLBuffer[relPosition] = bufArray[i];
                            break;
                    }
                }
                relPosition++;
            }
        }
        /* Clear the rest of the positions to the right of value */
        while(relPosition < digits)
        {
            switch(choiceReg)
            {
                case LED_SEG_REG_LOW :
                    LED_segLBuffer[relPosition] = LED_CLEAR;
                    break;
                case LED_SEG_REG_MID :
                    #if (LED_NUM_SEG > 8u)
                        LED_segMBuffer[relPosition] = LED_CLEAR;
                    #endif /* (LED_NUM_SEG > 8u) */
                    break;
                case LED_SEG_REG_HIGH :
                    #if (LED_NUM_SEG > 16u)
                        LED_segHBuffer[relPosition] = LED_CLEAR;
                    #endif /* (LED_NUM_SEG > 16u) */
                    break;
                default :
                    LED_segLBuffer[relPosition] = LED_CLEAR;
                    break;
            }
            relPosition++;
        }
    }
    else
    {
        /* Alignment for Right and zero padded */
        for(i = digits; i > 0u; i--)
        {
            if(((i + relPosition) - 1u) < LED_NUM_COM)
            {
                /* Decide which row to use */
                switch(choiceReg)
                {
                    case LED_SEG_REG_LOW :
                        LED_segLBuffer[(i + relPosition) - 1u] = bufArray[i-1u];
                        break;
                    case LED_SEG_REG_MID :
                        #if (LED_NUM_SEG > 8u)
                            LED_segMBuffer[(i + relPosition) - 1u] = bufArray[i-1u];
                        #endif /* (LED_NUM_SEG > 8u) */
                        break;
                    case LED_SEG_REG_HIGH :
                        #if (LED_NUM_SEG > 16u)
                            LED_segHBuffer[(i + relPosition) - 1u] = bufArray[i-1u];
                        #endif /* (LED_NUM_SEG > 16u) */
                        break;
                    default :
                        LED_segLBuffer[(i + relPosition) - 1u] = bufArray[i-1u];
                        break;
                }
            }
        }
    }
}


/*******************************************************************************
* Function Name: LED_Write7SegNumberHex
********************************************************************************
*
* Summary:
*  Displays a hexadecimal number up to 8 characters long, starting at 'position'
*  and extending for 'digits' characters. If you do not use the correct number 
*  of digits for your number, the least significant digits will be displayed. 
*  For example, if value is 0xDEADBEEF, display is 0 and digits is 4, the result 
*  will be: BEEF.
*
* Parameters:
*  uint32 number: The hexadecimal number to display. It is the responsibility of
*                 the user to ensure that the display has enough digits to 
*                 accurately representthe number passed to this function. If 
*                 not, the least significant digits will be displayed.
*  uint8 position: Position of the Display/Common to start number.
*  uint8 digits: The number of digits you wish to use to display the value 
*                passed into the function. If you do not use the correct number 
*                of digits for your number, the least significant digits will be
*                displayed.
*  uint8 alignment: How to align the provided number in the allocated digits.
*       RIGHT_ALIGN - Least significant digit occupies the rightmost digit
*                     (position + digits). Unused digits are turned off unless
*                     ZERO_PAD enabled.
*       LEFT_ALIGN - Most significant digit (or negative sign) occupies the
*                    digit specified by position. Unused digits are turned off.
*       ZERO_PAD - Unused digits to the left are padded with leading zeros.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Write7SegNumberHex(uint32 number, uint8 position, uint8 digits, uint8 alignment)

{
    uint8 i;
    uint8 relPosition;
    uint8 choiceReg;
    uint8 selectVal;
    uint8 zeroCount = 0u;
    uint8 bufArray[8u] = {0u};
    uint32 numberVal;
        
    numberVal = number;
    
    /* Choose to use either the low, mid or high control registers */
    if(position < LED_NUM_COM)
    {
        choiceReg = LED_SEG_REG_LOW;
        relPosition = position;
    }
    else if (position < LED_TWO_NUM_COM)
    {
        choiceReg = LED_SEG_REG_MID;
        relPosition = position - LED_NUM_COM;
    }
    else
    {
        choiceReg = LED_SEG_REG_HIGH;
        relPosition = position - LED_TWO_NUM_COM;
    }
    
    /* Fill up the temporary array */
    for(i = digits; i > 0u; i--)
    {
        selectVal = (uint8)((uint8)numberVal & LED_NIBBLE_MASK);
        bufArray[i-1u] = LED_EncodeNumber7Seg(selectVal);
        numberVal = (uint32)((uint32)numberVal >> LED_SHIFT_NIBBLE);
    }
    
    /* Clean up the array */
    if(alignment != LED_ZERO_PAD)
    {
        for(i = 0u; i < digits; i++)
        {
            if (bufArray[i] != LED_ZERO_7CHAR)
            {
                /* Exit when encountering non-zero number */
                break;
            }
            else
            {
                if(zeroCount != (digits - 1u))
                {
                    /* Turn off the display */
                    bufArray[i] = LED_CLEAR;
                    zeroCount++;
                }
            }    
        }
    }
    
    /* Place the values in the segment array according to alignment */
    if(alignment == LED_LEFT_ALIGN)
    {
        for(i = 0u; i < digits; i++)
        {
            if(bufArray[i] != LED_CLEAR)
            {
                if(relPosition < LED_NUM_COM)
                {
                    /* Only show displays that are not empty */
                    switch(choiceReg)
                    {
                        case LED_SEG_REG_LOW :
                            LED_segLBuffer[relPosition] = bufArray[i];
                            break;
                        case LED_SEG_REG_MID :
                            #if (LED_NUM_SEG > 8u)
                                LED_segMBuffer[relPosition] = bufArray[i];
                            #endif /* (LED_NUM_SEG > 8u) */
                            break;
                        case LED_SEG_REG_HIGH :
                            #if (LED_NUM_SEG > 16u)
                                LED_segHBuffer[relPosition] = bufArray[i];
                            #endif /* (LED_NUM_SEG > 16u) */
                            break;
                        default :
                            LED_segLBuffer[relPosition] = bufArray[i];
                            break;
                    }
                }
                relPosition++;
            }
        }
        /* Clear the rest of the positions to the right of value */
        while(relPosition < digits)
        {
            switch(choiceReg)
            {
                case LED_SEG_REG_LOW :
                    LED_segLBuffer[relPosition] = LED_CLEAR;
                    break;
                case LED_SEG_REG_MID :
                    #if (LED_NUM_SEG > 8u)
                        LED_segMBuffer[relPosition] = LED_CLEAR;
                    #endif /* (LED_NUM_SEG > 8u) */
                    break;
                case LED_SEG_REG_HIGH :
                    #if (LED_NUM_SEG > 16u)
                        LED_segHBuffer[relPosition] = LED_CLEAR;
                    #endif /* (LED_NUM_SEG > 16u) */
                    break;
                default :
                    LED_segLBuffer[relPosition] = LED_CLEAR;
                    break;
            }
            relPosition++;
        }
    }
    else
    {
        /* Alignment for right and zero padded */
        for(i = digits; i > 0u; i--)
        {
            if(((i + relPosition) - 1u) < LED_NUM_COM)
            {
                /* Decide which row to use */
                switch(choiceReg)
                {
                    case LED_SEG_REG_LOW :
                        LED_segLBuffer[(i + relPosition) - 1u] = bufArray[i-1u];
                        break;
                    case LED_SEG_REG_MID :
                        #if (LED_NUM_SEG > 8u)
                            LED_segMBuffer[(i + relPosition) - 1u] = bufArray[i-1u];
                        #endif /* (LED_NUM_SEG > 8u) */
                        break;
                    case LED_SEG_REG_HIGH :
                        #if (LED_NUM_SEG > 16u)
                            LED_segHBuffer[(i + relPosition) - 1u] = bufArray[i-1u];
                        #endif /* (LED_NUM_SEG > 16u) */
                        break;
                    default :
                        LED_segLBuffer[(i + relPosition) - 1u] = bufArray[i-1u];
                        break;
                }
            }
        }
    }
}


/*******************************************************************************
* Function Name: LED_WriteString7Seg
********************************************************************************
*
* Summary:
*  Displays a null terminated string starting at 'position' and ending at either
*  at the end the string or the end of the display. The displayable characters 
*  are the same for the LED_Driver_PutChar7Seg() function. Non-displayable
*  characters will produce a blank space.
*
* Parameters:
*  char8 const character[]: The null terminated string to be displayed.
*  uint8 position: The position to start the string.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_WriteString7Seg(char8 const character[], uint8 position)

{
    uint8 relPosition;
    uint8 sizeLimit;
    uint8 i = 0u;
    
    if(position < LED_NUM_COM)
    {
        sizeLimit = (uint8)(strlen(character)) + position;
        for(relPosition = position; relPosition < LED_NUM_COM; relPosition++)
        {
            if(relPosition < sizeLimit)
            {
                LED_segLBuffer[relPosition] = LED_EncodeChar7Seg(character[i]);
                i++;
            }
        }
    }    
    else if (position < LED_TWO_NUM_COM)
    {
        #if (LED_NUM_SEG > 8u) 
            sizeLimit = ((uint8)(strlen(character)) + position) - LED_NUM_COM;
            for(relPosition = position - LED_NUM_COM;
                relPosition < LED_NUM_COM; 
                relPosition++)
            {
                if(relPosition < sizeLimit)
                {
                    LED_segMBuffer[relPosition] = LED_EncodeChar7Seg(character[i]);
                    i++;
                }
            }
        #endif /* (LED_NUM_SEG > 8u) */
    }
    else
    {
        #if (LED_NUM_SEG > 16u)
            sizeLimit = ((uint8)(strlen(character)) + position) - LED_TWO_NUM_COM;
            for(relPosition = position - LED_TWO_NUM_COM;
                relPosition < LED_NUM_COM; 
                relPosition++)
            {
                if(relPosition < sizeLimit)
                {
                    LED_segHBuffer[relPosition] = LED_EncodeChar7Seg(character[i]);
                    i++;
                }    
            }
        #endif /* (LED_NUM_SEG > 16u) */
    }
}


/*******************************************************************************
* Function Name: LED_PutChar7Seg
********************************************************************************
*
* Summary:
*  Displays an ascii encoded character at 'position'. This function can display 
*  all alphanumeric characters. The function can also display '-', '.', '_', 
*  ' ', and '='. All unknown characters are displayed as a space.
*
* Parameters:
*  char8 character: ASCII character.
*  uint8 position: The position of the character.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_PutChar7Seg(char8 character , uint8 position)

{
    uint8 relPosition;
    
    if(position < LED_NUM_COM)
    {
        relPosition = position;
        LED_segLBuffer[relPosition] = LED_EncodeChar7Seg(character);
    }    
    else if (position < LED_TWO_NUM_COM)
    {
        #if (LED_NUM_SEG > 8u) 
            relPosition = position - LED_NUM_COM;
            LED_segMBuffer[relPosition] = LED_EncodeChar7Seg(character);
        #endif /* (LED_NUM_SEG > 8u) */
    }
    else
    {
        #if (LED_NUM_SEG > 16u)
            relPosition = position - LED_TWO_NUM_COM;
            if(relPosition < LED_NUM_COM)
            {
                LED_segHBuffer[relPosition] = LED_EncodeChar7Seg(character);
            }
        #endif /* (LED_NUM_SEG > 16u) */
    }
}


/*******************************************************************************
* Function Name: LED_Write7SegDigitDec
********************************************************************************
*
* Summary:
*  Displays a single digit on the specified display. The number in 'digit' 
*  (0-9) is placed on 'position.'
*
* Parameters:
*  uint8 digit: A number between 0 and 9 to display.
*  uint8 position: Position of the display in which to place the number.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Write7SegDigitDec(uint8 digit, uint8 position)

{
    uint8 relPosition;
    
    /* Only display numerical values */
    if (digit < 10u)
    {
        if(position < LED_NUM_COM)
        {
            relPosition = position;
            LED_segLBuffer[relPosition] = LED_EncodeNumber7Seg(digit);
        }    
        else if (position < LED_TWO_NUM_COM)
        {
            #if (LED_NUM_SEG > 8u)
                relPosition = position - LED_NUM_COM;
                LED_segMBuffer[relPosition] = LED_EncodeNumber7Seg(digit);
            #endif /* (LED_NUM_SEG > 8u) */
        } 
        else
        {
            #if (LED_NUM_SEG > 16u)
                relPosition = position - LED_TWO_NUM_COM;
                if(relPosition < LED_TWO_NUM_COM)
                {
                    LED_segHBuffer[relPosition] = LED_EncodeNumber7Seg(digit);
                }
            #endif /* (LED_NUM_SEG > 16u) */
        }
    }
}


/*******************************************************************************
* Function Name: LED_Write7SegDigitHex
********************************************************************************
*
* Summary:
*  Displays a single digit at the specified position. The number in 'digit' 
*  (0-F) is placed on 'position'.
*
* Parameters:
*  uint8 digit: A number between 0x0 and 0xF (0 to 15)
*  uint8 position: The position in which to place the number.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Write7SegDigitHex(uint8 digit, uint8 position)

{
    uint8 relPosition;
    
    if(position < LED_NUM_COM)
    {
        relPosition = position;
        LED_segLBuffer[relPosition] = LED_EncodeNumber7Seg(digit);
    }    
    else if (position < LED_TWO_NUM_COM)
    {
        #if (LED_NUM_SEG > 8u) 
            relPosition = position - LED_NUM_COM;
            LED_segMBuffer[relPosition] = LED_EncodeNumber7Seg(digit);
        #endif /* (LED_NUM_SEG > 8u) */
    }
    else
    {
        #if (LED_NUM_SEG > 16u)
            relPosition = position - LED_TWO_NUM_COM;
            if(relPosition < LED_NUM_COM)
            {
                LED_segHBuffer[relPosition] = LED_EncodeNumber7Seg(digit);
            }
        #endif /* (LED_NUM_SEG > 16u) */
    }
}


/*******************************************************************************
* Function Name: LED_Write14SegNumberDec
********************************************************************************
*
* Summary:
*  Displays a signed integer up to 8 characters long, starting at 'position' and
*  extending for 'digits' characters. The negative sign will take an extra digit
*  if it is required. If you do not use the correct number of digits for your 
*  number, only the least significant digits will be displayed.
*
* Parameters:
*  int32 number: a signed integer number to display. It is the responsibility 
*                of the user to ensure that the display has enough digits to 
*                accurately represent the number passed to this function. Note 
*                that a negative number will require 1 more digit than the 
*                equivalent positive number to display the negative sign.
*  uint8 position: Digit position of the Display/Common RAM to start.
*  uint8 digits: The number of digits you wish to use to display the value 
*                passed into the function. The negative sign will take an extra
*                digit if it is required.
*  uint8 alignment: How to align the provided number in the allocated digits.
*       RIGHT_ALIGN - Least significant digit occupies the rightmost digit
*                     (position + digits). Unused digits are turned off unless
*                     ZERO_PAD enabled.
*       LEFT_ALIGN - Most significant digit (or negative sign) occupies the
*                    digit specified by position. Unused digits are turned off.
*       ZERO_PAD - Unused digits to the left are padded with leading zeros.
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Write14SegNumberDec(int32 number, uint8 position, uint8 digits, uint8 alignment)

{
    uint8 i;
    uint8 relPosition;
    uint8 numberSign;
    uint8 selectVal;
    uint8 zeroCount = 0u;
    uint16 bufArray[8u] = {0u};
    uint32 numberVal;
        
    /* Routine to extract the sign and to convert to unsigned */
    if(number >= LED_ZERO_NEG)
    {
        numberVal = (uint32)number;
        numberSign = LED_UNSIGNED;
    }
    else
    {
        numberVal = (uint32)(-number);
        numberSign = LED_SIGNED;
    }
    
    /* Fill up the temporary array */
    for(i = digits; i > 0u; i--)
    {
        selectVal = (uint8)(numberVal % 10u);
        bufArray[i-1u] = LED_EncodeNumber14Seg(selectVal);
        numberVal = numberVal / 10u;
    }
    
    /* Clean up the array and place sign if needed */
    if(alignment == LED_ZERO_PAD)
    {
        if(numberSign == LED_SIGNED)
        {
            /* Place sign on the MSB */
            bufArray[0u] = LED_EncodeChar14Seg('-');
        }
    }
    else
    {
        for(i = 0u; i < digits; i++)
        {
            if (bufArray[i] != LED_ZERO_14CHAR)
            {
                if(numberSign == LED_SIGNED)
                {
                    if(i == 0u)
                    {
                        /* Place sign on the MSB */
                        bufArray[i] = LED_EncodeChar14Seg('-');
                    }
                    else
                    {
                        /* Place sign before MSB */
                        bufArray[i-1u] = LED_EncodeChar14Seg('-');
                    }
                }
                /* Exit when encountering non-zero number */
                break;
            }
            else
            {
                if(zeroCount != (digits - 1u))
                {
                    /* Turn off the display */
                    bufArray[i] = LED_CLEAR_16;
                    zeroCount++;
                }
            }    
        }
    }
    
    relPosition = position;
    
    /* Place the values in the segment array according to alignment */
    if(alignment == LED_LEFT_ALIGN)
    {
        for(i = 0u; i < digits; i++)
        {
            if(bufArray[i] != LED_CLEAR_16)
            {
                if(relPosition < LED_NUM_COM)
                {
                    /* Only show displays that are not empty */
                    LED_segLBuffer[relPosition] = LO8(bufArray[i]);
                #if (LED_NUM_SEG > 8u)
                    LED_segMBuffer[relPosition] = HI8(bufArray[i]);
                #endif /* (LED_NUM_SEG > 8u) */
                }
                relPosition++;
            }
        }
        /* Clear the rest of the positions to the right of value */
        while(relPosition < digits)
        {
            /* Only show displays that are not empty */
            LED_segLBuffer[relPosition] = LED_CLEAR;
            #if (LED_NUM_SEG > 8u)
                LED_segMBuffer[relPosition] = LED_CLEAR;
            #endif /* (LED_NUM_SEG > 8u) */
            
            relPosition++;
        }
    }
    else
    {
        for(i = digits; i > 0u; i--)
        {
            if(((i + relPosition) - 1u) < LED_NUM_COM)
            {
                LED_segLBuffer[(i + relPosition) - 1u] = LO8(bufArray[i-1u]);
            #if (LED_NUM_SEG > 8u)
                LED_segMBuffer[(i + relPosition) - 1u] = HI8(bufArray[i-1u]);
            #endif /* (LED_NUM_SEG > 8u) */
            }
        }  
    }
}


/*******************************************************************************
* Function Name: LED_Write14SegNumberHex
********************************************************************************
*
* Summary:
*  Displays a hexadecimal number up to 8 characters long, starting at 'position'
*  and extending for 'digits' characters. If you do not use the correct number
*  of digits for your number, the least significant digits will be displayed. 
*  For example, if value is 0xDEADBEEF, display is 0 and digits is 4, the result
*  will be: BEEF.
*
* Parameters:
*  uint32 number: The hexadecimal number to display. It is the responsibility 
*                 of the user to ensure that the display has enough digits to 
*                 accurately represent the number passed to this function. If 
*                 not, only the least significant digits will be displayed.
*  uint8 position: Position of the Display/Common to start number.
*  uint8 digits: The number of digits you wish to use to display the value 
*                passed into the function. If you do not use the correct number
*                of digits for your number, the least significant digits will 
*                be displayed.
*  uint8 alignment: How to align the provided number in the allocated digits.
*       RIGHT_ALIGN - Least significant digit occupies the rightmost digit
*                     (position + digits). Unused digits are turned off unless
*                     ZERO_PAD enabled.
*       LEFT_ALIGN - Most significant digit (or negative sign) occupies the
*                    digit specified by position. Unused digits are turned off.
*       ZERO_PAD - Unused digits to the left are padded with leading zeros.
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Write14SegNumberHex(uint32 number, uint8 position, uint8 digits, uint8 alignment)

{
    uint8 i;
    uint8 relPosition;
    uint8 selectVal;
    uint16 bufArray[8u] = {0u};
    uint32 numberVal;
    
    numberVal = number;
    
    /* Fill up the temporary array */
    for(i = digits; i > 0u; i--)
    {
        selectVal = (uint8)((uint8)numberVal & LED_NIBBLE_MASK);
        bufArray[i-1u] = LED_EncodeNumber14Seg(selectVal);
        numberVal = (uint32)((uint32)numberVal >> LED_SHIFT_NIBBLE);
    }
    
    /* Clean up the array */
    for(i = 0u; i < digits; i++)
    {
        if (bufArray[i] != LED_ZERO_14CHAR)
        {
            /* Exit when encountering non-zero number */
            break;
        }
        else
        {
            /* Turn off the display */
            bufArray[i] = LED_CLEAR_16;
        }    
    }
    
    relPosition = position;
    
    /* Place the values in the segment array according to alignment */
    if(alignment == LED_LEFT_ALIGN)
    {
        for(i = 0u; i < digits; i++)
        {
            if(bufArray[i] != LED_CLEAR_16)
            {
                if(relPosition < LED_NUM_COM)
                {
                    /* Only show displays that are not empty */
                    LED_segLBuffer[relPosition] = LO8(bufArray[i]);
                #if (LED_NUM_SEG > 8u)
                    LED_segMBuffer[relPosition] = HI8(bufArray[i]);
                #endif /* (LED_NUM_SEG > 8u) */
                }
                relPosition++;
            }
        }
        /* Clear the rest of the positions to the right of value */
        while(relPosition < digits)
        {
            /* Only show displays that are not empty */
            LED_segLBuffer[relPosition] = LED_CLEAR;
            #if (LED_NUM_SEG > 8u)
                LED_segMBuffer[relPosition] = LED_CLEAR;
            #endif /* (LED_NUM_SEG > 8u) */
            
            relPosition++;
        }
    }
    else
    {
        for(i = digits; i > 0u; i--)
        {
            if(((i + relPosition) - 1u) < LED_NUM_COM)
            {
                LED_segLBuffer[(i + relPosition) - 1u] = LO8(bufArray[i-1u]);
            #if (LED_NUM_SEG > 8u)
                LED_segMBuffer[(i + relPosition) - 1u] = HI8(bufArray[i-1u]);
            #endif /* (LED_NUM_SEG > 8u) */
            }
        }  
    }
}


/*******************************************************************************
* Function Name: LED_WriteString14Seg
********************************************************************************
*
* Summary:
*  Displays a null terminated string starting at 'position' and ending at 
*  either the  the string or the  the display. The displayable 
*  characters are the same for the LED_Driver_PutCharacter() function. 
*  Non-displayable characters will produce a blank space.
*
* Parameters:
*  char8 const character[]: The null terminated string to be displayed.
*  uint8 position: The position to start the string.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_WriteString14Seg(char8 const character[], uint8 position)

{
    uint8 currPosition;
    uint8 sizeLimit;
    uint8 i = 0u;
    uint16 charDisplay;
    
    sizeLimit = (uint8)(strlen(character)) + position;
    
    for(currPosition = position; currPosition < LED_NUM_COM; currPosition++)
    {
        if(currPosition < sizeLimit)
        {
            charDisplay = LED_EncodeChar14Seg(character[i]);
            LED_segLBuffer[currPosition] = LO8(charDisplay);
            #if (LED_NUM_SEG > 8u)
            LED_segMBuffer[currPosition] = HI8(charDisplay);
            #endif /* (LED_NUM_SEG > 8u) */
            i++;
        }
    }
}


/*******************************************************************************
* Function Name: LED_PutChar14Seg
********************************************************************************
*
* Summary:
*  Displays an ascii encoded character at 'position'. This function can display
*  all alphanumeric characters. The function can also display '-', '.', '_', 
*  ' ', and '='. All unknown characters are displayed as a space.
*
* Parameters:
*  char8 character: ASCII character.
*  uint8 position: The position of the character.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_PutChar14Seg(char8 character , uint8 position)

{
    uint16 charDisplay;
    
    if(position < LED_NUM_COM)
    {
        charDisplay = LED_EncodeChar14Seg(character);
        LED_segLBuffer[position] = LO8(charDisplay);
    #if (LED_NUM_SEG > 8u)
        LED_segMBuffer[position] = HI8(charDisplay);
    #endif /* (LED_NUM_SEG > 8u) */
    }
}


/*******************************************************************************
* Function Name: LED_Write14SegDigitDec
********************************************************************************
*
* Summary:
*  Displays a single digit on the specified display. The number in 'digit' 
*  (0-9) is placed on 'position'.
*
* Parameters:
*  uint8 digit: A number between 0 and 9 to display.
*  uint8 position: Position of the display in which to place the number.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Write14SegDigitDec(uint8 digit, uint8 position)

{
    uint16 charDisplay;
    
    if((digit < 10u) && (position < LED_NUM_COM))
    {
        charDisplay = LED_EncodeNumber14Seg(digit);
        LED_segLBuffer[position] = LO8(charDisplay);
    #if (LED_NUM_SEG > 8u)
        LED_segMBuffer[position] = HI8(charDisplay);
    #endif /* (LED_NUM_SEG > 8u) */
    }
}


/*******************************************************************************
* Function Name: LED_Write14SegDigitHex
********************************************************************************
*
* Summary:
*  Displays a single digit at the specified position. The number in 'digit' 
*  (0-F) is placed on 'position'.
*
* Parameters:
*  uint8 digit: A number between 0x0 and 0xF (0 to 15)
*  uint8 position: The position in which to place the number.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Write14SegDigitHex(uint8 digit, uint8 position)

{
    uint16 charDisplay;

    if(position < LED_NUM_COM)
    {
        charDisplay = LED_EncodeNumber14Seg(digit);
        LED_segLBuffer[position] = LO8(charDisplay);
    #if (LED_NUM_SEG > 8u)
        LED_segMBuffer[position] = HI8(charDisplay);
    #endif /* (LED_NUM_SEG > 8u) */
    }
}


/*******************************************************************************
* Function Name: LED_Write16SegNumberDec
********************************************************************************
*
* Summary:
*  Displays a signed integer up to 8 characters long, starting at 'position' 
*  and extending for 'digits' characters. The negative sign will take an extra 
*  digit if it is required.
*
* Parameters:
*  int32 number: a signed integer number to display. It is the responsibility 
*                of the user to ensure that the display has enough digits to 
*                accurately represent the number passed to this function. If 
*                not, the least significant digits will be displayed. Also 
*                note that a negative number will require 1 more digit than the
*                equivalent positive number to display the negative sign.
*  uint8 position: Digit position of the Display/Common RAM to start.
*  uint8 digits: The number of digits you wish to use to display the value 
*                passed into the function. The negative sign will take an extra 
*                digit if it is required.
*  uint8 alignment: How to align the provided number in the allocated digits.
*       RIGHT_ALIGN - Least significant digit occupies the rightmost digit
*                     (position + digits). Unused digits are turned off unless
*                     ZERO_PAD enabled.
*       LEFT_ALIGN - Most significant digit (or negative sign) occupies the
*                    digit specified by position. Unused digits are turned off.
*       ZERO_PAD - Unused digits to the left are padded with leading zeros.
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Write16SegNumberDec(int32 number, uint8 position, uint8 digits, uint8 alignment)

{
    uint8 i;
    uint8 relPosition;
    uint8 numberSign;
    uint8 selectVal;
    uint8 zeroCount = 0u;
    uint16 bufArray[8u] = {0u};
    uint32 numberVal;
    
    /* Routine to extract the sign and to convert to unsigned */
    if(number >= LED_ZERO_NEG)
    {
        numberVal = (uint32)number;
        numberSign = LED_UNSIGNED;
    }
    else
    {
        numberVal = (uint32)(-number);
        numberSign = LED_SIGNED;
    }
    
    /* Fill up the temporary array */
    for(i = digits; i > 0u; i--)
    {
        selectVal = (uint8)(numberVal % 10u);
        bufArray[i-1u] = LED_EncodeNumber16Seg(selectVal);
        numberVal = numberVal / 10u;
    }
    
    /* Clean up the array and place sign if needed */
    if(alignment == LED_ZERO_PAD)
    {
        if(numberSign == LED_SIGNED)
        {
            /* Place sign on the MSB */
            bufArray[0u] = LED_EncodeChar16Seg('-');
        }
    }
    else
    {
        for(i = 0u; i < digits; i++)
        {
            if (bufArray[i] != LED_ZERO_16CHAR)
            {
                if(numberSign == LED_SIGNED)
                {
                    if(i == 0u)
                    {
                        /* Place sign on the MSB */
                        bufArray[i] = LED_EncodeChar16Seg('-');
                    }
                    else
                    {
                        /* Place sign before MSB */
                        bufArray[i-1u] = LED_EncodeChar16Seg('-');
                    }
                }
                /* Exit when encountering non-zero number */
                break;
            }
            else
            {
                if(zeroCount != (digits - 1u))
                {
                    /* Turn off the display */
                    bufArray[i] = LED_CLEAR_16;
                    zeroCount++;
                }
            }    
        }
    }
    
    relPosition = position;
    
    /* Place the values in the segment array according to alignment */
    if(alignment == LED_LEFT_ALIGN)
    {
        for(i = 0u; i < digits; i++)
        {
            if(bufArray[i] != LED_CLEAR_16)
            {
                if(relPosition < LED_NUM_COM)
                {
                    /* Only show displays that are not empty */
                    LED_segLBuffer[relPosition] = LO8(bufArray[i]);
                #if (LED_NUM_SEG > 8u)
                    LED_segMBuffer[relPosition] = HI8(bufArray[i]);
                #endif /* (LED_NUM_SEG > 8u) */
                }
                relPosition++;
            }
        }
        /* Clear the rest of the positions to the right of value */
        while(relPosition < digits)
        {
            /* Only show displays that are not empty */
            LED_segLBuffer[relPosition] = LED_CLEAR;
            #if (LED_NUM_SEG > 8u)
                LED_segMBuffer[relPosition] = LED_CLEAR;
            #endif /* (LED_NUM_SEG > 8u) */
            
            relPosition++;
        }
    }
    else
    {
        for(i = digits; i > 0u; i--)
        {
            if(((i + relPosition) - 1u) < LED_NUM_COM)
            {
                LED_segLBuffer[(i + relPosition) - 1u] = LO8(bufArray[i-1u]);
            #if (LED_NUM_SEG > 8u)
                LED_segMBuffer[(i + relPosition) - 1u] = HI8(bufArray[i-1u]);
            #endif /* (LED_NUM_SEG > 8u) */
            }
        }
    }
}


/*******************************************************************************
* Function Name: LED_Write16SegNumberHex
********************************************************************************
*
* Summary:
*  Displays a hexadecimal number up to 8 characters long, starting at 'position'
*  and extending for 'digits' characters. If you do not use the correct number 
*  of digits for your number, the least significant digits will be displayed. 
*  For example, if value is 0xDEADBEEF, display is 0 and digits is 4, the result
*  will be: BEEF.
*
* Parameters:
*  uint32 number: The hexadecimal number to display. It is the responsibility of
*  the user to ensure that the display has enough digits to accurately represent
*  the number passed to this function.
*  uint8 position: Position of the Display/Common to start number.
*  uint8 digits: The number of digits you wish to use to display the value 
*                passed into the function.
*  uint8 alignment: How to align the provided number in the allocated digits.
*       RIGHT_ALIGN - Least significant digit occupies the rightmost digit
*                     (position + digits). Unused digits are turned off unless
*                     ZERO_PAD enabled.
*       LEFT_ALIGN - Most significant digit (or negative sign) occupies the
*                    digit specified by position. Unused digits are turned off.
*       ZERO_PAD - Unused digits to the left are padded with leading zeros.
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Write16SegNumberHex(uint32 number, uint8 position, uint8 digits, uint8 alignment)

{
    uint8 i;
    uint8 relPosition;
    uint8 selectVal;
    uint16 bufArray[8u] = {0u};
    uint32 numberVal;
    
    numberVal = number;
    
    /* Fill up the temporary array */
    for(i = digits; i > 0u; i--)
    {
        selectVal = (uint8)((uint8)numberVal & LED_NIBBLE_MASK);
        bufArray[i-1u] = LED_EncodeNumber16Seg(selectVal);
        numberVal = (uint32)((uint32)numberVal >> LED_SHIFT_NIBBLE);
    }
    
    /* Clean up the array and place sign if needed */
    for(i = 0u; i < digits; i++)
    {
        if (bufArray[i] != LED_ZERO_16CHAR)
        {
            /* Exit when encountering non-zero number */
            break;
        }
        else
        {
            /* Turn off the display */
            bufArray[i] = LED_CLEAR_16;
        }    
    }
    
    relPosition = position;
    
    /* Place the values in the segment array according to alignment */
    if(alignment == LED_LEFT_ALIGN)
    {
        for(i = 0u; i < digits; i++)
        {
            if(bufArray[i] != LED_CLEAR_16)
            {
                if(relPosition < LED_NUM_COM)
                {
                    /* Only show displays that are not empty */
                    LED_segLBuffer[relPosition] = LO8(bufArray[i]);
                #if (LED_NUM_SEG > 8u)
                    LED_segMBuffer[relPosition] = HI8(bufArray[i]);
                #endif /* (LED_NUM_SEG > 8u) */
                }
                relPosition++;
            }
        }
        /* Clear the rest of the positions to the right of value */
        while(relPosition < digits)
        {
            /* Only show displays that are not empty */
            LED_segLBuffer[relPosition] = LED_CLEAR;
            #if (LED_NUM_SEG > 8u)
                LED_segMBuffer[relPosition] = LED_CLEAR;
            #endif /* (LED_NUM_SEG > 8u) */
            
            relPosition++;
        }
    }
    else
    {
        for(i = digits; i > 0u; i--)
        {
            if(((i + relPosition) - 1u) < LED_NUM_COM)
            {
                LED_segLBuffer[(i + relPosition) - 1u] = LO8(bufArray[i-1u]);
            #if (LED_NUM_SEG > 8u)
                LED_segMBuffer[(i + relPosition) - 1u] = HI8(bufArray[i-1u]);
            #endif /* (LED_NUM_SEG > 8u) */
            }
        }
    }
}


/*******************************************************************************
* Function Name: LED_WriteString16Seg
********************************************************************************
*
* Summary:
*  Displays a null terminated string starting at 'position' and ending at either
*  the  the string or the  the display. The displayable characters 
*  are the same for the LED_Driver_PutCharacter() function. Non-displayable
*  characters will produce a blank space.
*
* Parameters:
*  char8 const character[]: The null terminated string to be displayed.
*  uint8 position: The position to start the string.
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_WriteString16Seg(char8 const character[], uint8 position)

{
    uint8 currPosition;
    uint8 sizeLimit;
    uint8 i = 0u;
    uint16 charDisplay;
    
    sizeLimit = (uint8)(strlen(character)) + position;
    
    for(currPosition = position; currPosition < LED_NUM_COM; currPosition++)
    {
        if(currPosition < sizeLimit)
        {
            charDisplay = LED_EncodeChar16Seg(character[i]);
            LED_segLBuffer[currPosition] = LO8(charDisplay);
            #if (LED_NUM_SEG > 8u)
                LED_segMBuffer[currPosition] = HI8(charDisplay);
            #endif /* (LED_NUM_SEG > 8u) */
            i++;
        }
    }
}


/*******************************************************************************
* Function Name: LED_PutChar16Seg
********************************************************************************
*
* Summary:
*  Displays an ascii encoded character at 'position'. This function can display 
*  all alphanumeric characters. The function can also display '-', '.', '_', 
*  ' ', and '='. All unknown characters are displayed as a space.
*
* Parameters:
*  char8 character: ASCII character.
*  uint8 position: The position of the character.
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_PutChar16Seg(char8 character , uint8 position)

{
    uint16 charDisplay;
    
    if(position < LED_NUM_COM)
    {
        charDisplay = LED_EncodeChar16Seg(character);
        LED_segLBuffer[position] = LO8(charDisplay);
        #if (LED_NUM_SEG > 8u)
            LED_segMBuffer[position] = HI8(charDisplay);
        #endif /* (LED_NUM_SEG > 8u) */
    }
}


/*******************************************************************************
* Function Name: LED_Write16SegDigitDec
********************************************************************************
*
* Summary:
*  Displays a single digit on the specified display. The number in 'digit' 
*  (0-9) is placed on 'position'.
*
* Parameters:
*  uint8 digit: A number between 0 and 9 to display.
*  uint8 position: Position of the display in which to place the number.
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Write16SegDigitDec(uint8 digit, uint8 position)

{
    uint16 charDisplay;
    
    if((digit < 10u) && (position < LED_NUM_COM))
    {
        charDisplay = LED_EncodeNumber16Seg(digit);
        LED_segLBuffer[position] = LO8(charDisplay);
        #if (LED_NUM_SEG > 8u)
            LED_segMBuffer[position] = HI8(charDisplay);
        #endif /* (LED_NUM_SEG > 8u) */
    }
}


/*******************************************************************************
* Function Name: LED_Write16SegDigitHex
********************************************************************************
*
* Summary:
*  Displays a single digit at the specified position. The number in 'digit' 
*  (0-F) is placed on 'position'.
*
* Parameters:
*  uint8 digit: A number between 0x0 and 0xF (0 to 15).
*  uint8 position: The position in which to place the number.
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_Write16SegDigitHex(uint8 digit, uint8 position)

{
    uint16 charDisplay;

    if(position < LED_NUM_COM)
    {
        charDisplay = LED_EncodeNumber16Seg(digit);
        LED_segLBuffer[position] = LO8(charDisplay);
        #if (LED_NUM_SEG > 8u)
            LED_segMBuffer[position] = HI8(charDisplay);
        #endif /* (LED_NUM_SEG > 8u) */
    }
}


/*******************************************************************************
* Function Name: LED_PutDecimalPoint
********************************************************************************
*
* Summary:
*  Sets or clears the decimal point at the specified position.
*
* Parameters:
*  uint8 dp: If the value is > 0 the decimal point will be set, if zero, the 
*            decimal point will be cleared.
*  uint8 position: The position at which to adjust the decimal point.
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_PutDecimalPoint(uint8 dp, uint8 position)

{
    uint8 value;
    uint8 relPosition;
    
    value = LED_DEC_POINT_VALUE;
    
    if(position < LED_NUM_COM)
    {
        relPosition = position;
        if(dp != 0u)
        {
            #if(LED_SEG_DRIVE == LED_HIGH)
                LED_segLBuffer[relPosition] |= value;
            #else
                LED_segLBuffer[relPosition] &= value;
            #endif /* (LED_SEG_DRIVE == LED_HIGH) */
        }
        else
        {
            #if(LED_SEG_DRIVE == LED_HIGH)
                LED_segLBuffer[relPosition] &= ((uint8)(~(uint8)value));
            #else
                LED_segLBuffer[relPosition] |= ((uint8)(~(uint8)value));
            #endif /* (LED_SEG_DRIVE == LED_HIGH) */
        }
    } 
    else if (position < LED_TWO_NUM_COM)
    {
        #if (LED_NUM_SEG > 8u)
            relPosition = position - LED_NUM_COM;
            if(dp != 0u)
            {
                #if(LED_SEG_DRIVE == LED_HIGH)
                    LED_segMBuffer[relPosition] |= value;
                #else
                    LED_segMBuffer[relPosition] &= value;
                #endif /* (LED_SEG_DRIVE == LED_HIGH) */
            }
            else
            {
                #if(LED_SEG_DRIVE == LED_HIGH)
                    LED_segMBuffer[relPosition] &= ((uint8)(~(uint8)value));
                #else
                    LED_segMBuffer[relPosition] |= ((uint8)(~(uint8)value));
                #endif /* (LED_SEG_DRIVE == LED_HIGH) */
            }
        #endif /* (LED_NUM_SEG > 8u) */
    } 
    else
    {
        #if (LED_NUM_SEG > 16u)
            relPosition = position - LED_TWO_NUM_COM;
            if(relPosition < LED_NUM_COM)
            {
                if(dp != 0u)
                {
                    #if(LED_SEG_DRIVE == LED_HIGH)
                        LED_segHBuffer[relPosition] |= value;
                    #else
                        LED_segHBuffer[relPosition] &= value;
                    #endif /* (LED_SEG_DRIVE == LED_HIGH) */
                }
                else
                {
                    #if(LED_SEG_DRIVE == LED_HIGH)
                        LED_segHBuffer[relPosition] &= ((uint8)(~(uint8)value));
                    #else
                        LED_segHBuffer[relPosition] |= ((uint8)(~(uint8)value));
                    #endif /* (LED_SEG_DRIVE == LED_HIGH) */
                }
            }
        #endif /* (LED_NUM_SEG > 16u) */
    }
}


/*******************************************************************************
* Function Name: LED_GetDecimalPoint
********************************************************************************
*
* Summary:
*  Returns zero if the decimal point is not set and one if the decimal point 
*  is set.
*
* Parameters:
*  uint8 position: The position in which to query the decimal point value.
*
* Return:
*  Returns the current state of the decimal point (segment #7 on a 7-seg 
*  display). '1' indicates the decimal point is on. '0' indicates the decimal 
*  point is off.
*
* Side effects:
*  None
*
*******************************************************************************/
uint8 LED_GetDecimalPoint(uint8 position) 
{
    uint8 value;
    uint8 relPosition;
    uint8 decPointVal = 0u;
    
    if(position < LED_NUM_COM)
    {
        relPosition = position;
        decPointVal = (uint8)((uint8)(LED_segLBuffer[relPosition]) >> LED_DEC_POINT);
    } 
    else if (position < LED_TWO_NUM_COM)
    {
        #if (LED_NUM_SEG > 8u) 
            relPosition = position - LED_NUM_COM;
            decPointVal = (uint8)((uint8)(LED_segMBuffer[relPosition]) >> LED_DEC_POINT);
        #endif /* (LED_NUM_SEG > 8u) */
    }
    else
    {
        #if (LED_NUM_SEG > 16u)
            relPosition = position - LED_TWO_NUM_COM;
            if(relPosition < LED_NUM_COM)
            {
                decPointVal = (uint8)((uint8)(LED_segHBuffer[relPosition]) >> LED_DEC_POINT);
            }
        #endif /* (LED_NUM_SEG > 16u) */
    }
    
    #if(LED_SEG_DRIVE == LED_HIGH)
        value = (uint8)(decPointVal & LED_DEC_POINT_MASK);
    #else
        value = (uint8)((uint8)((uint8)~decPointVal) & LED_DEC_POINT_MASK);
    #endif /* (LED_SEG_DRIVE == LED_HIGH) */
    
    return(value);
}


/*******************************************************************************
* Function Name: LED_EncodeNumber7Seg
********************************************************************************
*
* Summary:
*  Converts the lower 4 bits of the input into 7-segment data that will display 
*  the number in hex on a display. The returned data can be written directly 
*  into the display RAM to display the desired number. It is not necessary to 
*  use this function since higher level API are provided to both decode the 
*  value and write it to the display RAM.
*
* Parameters:
*  uint8 number: A number between 0x0 and 0xF to be converted into segment data.
*
* Return:
*  The value to be written into the display RAM for displaying the specific
*  number.
*
* Side effects:
*  None
*
*******************************************************************************/
uint8 LED_EncodeNumber7Seg(uint8 number) 
{
    /* 7-segment numerical LUT */
    #if(LED_SEG_DRIVE == LED_HIGH)
        static const uint8 CYCODE LED_7SegDigits[16] =
              /*--------------------------------------------------------*/
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0x3fu, 0x06u, 0x5bu, 0x4fu, 0x66u, 0x6du, 0x7du, 0x07u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    'A'    'B'    'C'    'D'    'E'    'F'  */
              /*--------------------------------------------------------*/
                 0x7fu, 0x6fu, 0x77u, 0x7cu, 0x39u, 0x5eu, 0x79u, 0x71u};
    #else
        static const uint8 CYCODE LED_7SegDigits[16] =
              /*--------------------------------------------------------*/
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0xc0u, 0xf9u, 0xa4u, 0xb0u, 0x99u, 0x92u, 0x82u, 0xf8u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    'A'    'B'    'C'    'D'    'E'    'F'  */
              /*--------------------------------------------------------*/
                 0x80u, 0x90u, 0x88u, 0x83u, 0xc6u, 0xa1u, 0x86u, 0x8eu};
    #endif /*  LED_SEG_DRIVE */

    uint8 valNum;
    uint8 valHex;
    
    valNum = (uint8)(number & LED_NIBBLE_MASK);
    
    valHex = LED_7SegDigits[valNum];
    
    return(valHex);
}


/*******************************************************************************
* Function Name: LED_EncodeChar7Seg
********************************************************************************
*
* Summary:
*  Converts the ASCII encoded alphabet character input into the 7-segment data
*  that will display the alphabet character on a display. The returned data can
*  be written directly into the display RAM to display the desired number. It is
*  not necessary to use this function since higher level API are provided to 
*  both decode the value and write it to the display RAM.
*
* Parameters:
*  char8 input: An ASCII alphabet character to be converted into segment data.
*
* Return:
*  The value to be written into the display RAM for displaying the specified
*  character.
*
* Side effects:
*  None
*
*******************************************************************************/
uint8 LED_EncodeChar7Seg(char8 input)  
{
    /* 7-segment ASCII LUT */
    #if(LED_SEG_DRIVE == LED_HIGH)
        static const uint8 CYCODE LED_7SegASCII[6][16] =
              {
              /*--------------------------------------------------------*/
              /* 'Space' '!'    '"'    '#'    '$'    '%'    '&'    '''  */
              /*--------------------------------------------------------*/
                {0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
              /*--------------------------------------------------------*/
              /*  '('    ')'    '*'    '+'    ','    '-'    '.'    '/'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x40u, 0x80u, 0x00u},
              /*--------------------------------------------------------*/   
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0x3fu, 0x06u, 0x5bu, 0x4fu, 0x66u, 0x6du, 0x7du, 0x07u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    ':'    ';'    '<'    '='    '>'    '?'  */
              /*--------------------------------------------------------*/
                 0x7fu, 0x6fu, 0x00u, 0x00u, 0x00u, 0x48u, 0x00u, 0x00u},
              /*--------------------------------------------------------*/
              /*  '@'    'A'    'B'    'C'    'D'    'E'    'F'    'G'  */
              /*--------------------------------------------------------*/
                {0x00u, 0x77u, 0x7cu, 0x58u, 0x5eu, 0x79u, 0x71u, 0x3du,
              /*--------------------------------------------------------*/
              /*  'H'    'I'    'J'    'K'    'L'    'M'    'N'    'O'  */
              /*--------------------------------------------------------*/
                 0x74u, 0x10u, 0x1Eu, 0x76u, 0x38u, 0x55u, 0x54u, 0x5cu},
              /*--------------------------------------------------------*/
              /*  'P'    'Q'    'R'    'S'    'T'    'U'    'V'    'W'  */
              /*--------------------------------------------------------*/
                {0x73u, 0x67u, 0x50u, 0x6du, 0x78u, 0x1cu, 0x1cu, 0x1du,
              /*--------------------------------------------------------*/
              /*  'X'    'Y'    'Z'    '['    '\'    ']'    '^'    '_'  */
              /*--------------------------------------------------------*/
                 0x76u, 0x6eu, 0x5bu, 0x00u, 0x00u, 0x00u, 0x00u, 0x08u},
              /*--------------------------------------------------------*/
              /*  '`'    'a'    'b'    'c'    'd'    'e'    'f'    'g'  */
              /*--------------------------------------------------------*/
                {0x00u, 0x77u, 0x7cu, 0x58u, 0x5eu, 0x79u, 0x71u, 0x3du,
              /*--------------------------------------------------------*/
              /*  'h'    'i'    'j'    'k'    'l'    'm'    'n'    'o'  */
              /*--------------------------------------------------------*/
                 0x74u, 0x10u, 0x1Eu, 0x76u, 0x38u, 0x55u, 0x54u, 0x5cu},
              /*--------------------------------------------------------*/
              /*  'p'    'q'    'r'    's'    't'    'u'    'v'    'w'  */
              /*--------------------------------------------------------*/
                {0x73u, 0x67u, 0x50u, 0x6du, 0x78u, 0x1cu, 0x1cu, 0x1du,
              /*--------------------------------------------------------*/
              /*  'x'    'y'    'z'    '{'    '|'    '}'    '~'   'DEL' */
              /*--------------------------------------------------------*/
                 0x76u, 0x6eu, 0x5bu, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u}
              };
    #else
        static const uint8 CYCODE LED_7SegASCII[6][16] =
              {
              /*--------------------------------------------------------*/
              /* 'Space' '!'    '"'    '#'    '$'    '%'    '&'    '''  */
              /*--------------------------------------------------------*/
                {0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
              /*--------------------------------------------------------*/
              /*  '('    ')'    '*'    '+'    ','    '-'    '.'    '/'  */
              /*--------------------------------------------------------*/
                 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xBfu, 0x7fu, 0xffu},
              /*--------------------------------------------------------*/   
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0xc0u, 0xf9u, 0xa4u, 0xb0u, 0x99u, 0x92u, 0x82u, 0xf8u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    ':'    ';'    '<'    '='    '>'    '?'  */
              /*--------------------------------------------------------*/
                 0x80u, 0x90u, 0xffu, 0xffu, 0xffu, 0xb7u, 0xffu, 0xffu},
              /*--------------------------------------------------------*/
              /*  '@'    'A'    'B'    'C'    'D'    'E'    'F'    'G'  */
              /*--------------------------------------------------------*/
                {0xffu, 0x88u, 0x83u, 0xa7u, 0xa1u, 0x86u, 0x8eu, 0xc2u,
              /*--------------------------------------------------------*/
              /*  'H'    'I'    'J'    'K'    'L'    'M'    'N'    'O'  */
              /*--------------------------------------------------------*/
                 0x8bu, 0xefu, 0xe1u, 0x89u, 0xc7u, 0xaau, 0xabu, 0xa3u},
              /*--------------------------------------------------------*/
              /*  'P'    'Q'    'R'    'S'    'T'    'U'    'V'    'W'  */
              /*--------------------------------------------------------*/
                {0x8cu, 0x98u, 0xafu, 0x92u, 0x87u, 0xe3u, 0xe3u, 0xe2u,
              /*--------------------------------------------------------*/
              /*  'X'    'Y'    'Z'    '['    '\'    ']'    '^'    '_'  */
              /*--------------------------------------------------------*/
                 0x89u, 0x91u, 0xa4u, 0xffu, 0xffu, 0xffu, 0xffu, 0xf7u},
              /*--------------------------------------------------------*/
              /*  '`'    'a'    'b'    'c'    'd'    'e'    'f'    'g'  */
              /*--------------------------------------------------------*/
                {0xffu, 0x88u, 0x83u, 0xa7u, 0xa1u, 0x86u, 0x8eu, 0xc2u,
              /*--------------------------------------------------------*/
              /*  'h'    'i'    'j'    'k'    'l'    'm'    'n'    'o'  */
              /*--------------------------------------------------------*/
                 0x8bu, 0xefu, 0xe1u, 0x89u, 0xc7u, 0xaau, 0xabu, 0xa3u},
              /*--------------------------------------------------------*/
              /*  'p'    'q'    'r'    's'    't'    'u'    'v'    'w'  */
              /*--------------------------------------------------------*/
                {0x8cu, 0x98u, 0xafu, 0x92u, 0x87u, 0xe3u, 0xe3u, 0xe2u,
              /*--------------------------------------------------------*/
              /*  'x'    'y'    'z'    '{'    '|'    '}'    '~'   'DEL' */
              /*--------------------------------------------------------*/
                 0x89u, 0x91u, 0xa4u, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu}
              };
    #endif /*  LED_SEG_DRIVE */
    
    uint8 valLow;
    uint8 valHigh;
    uint8 valHex;
    
    valLow = (uint8)((uint8)input & LED_NIBBLE_MASK);
    
    /* valHigh used to access the row of LUT */
    valHigh = (uint8)((uint8)input >> LED_SHIFT_NIBBLE);
    
    /* Check if the high nibble is within valid ASCII range */
    if ((valHigh > LED_SEG_ASCII_LIM_LO) && (valHigh < LED_SEG_ASCII_LIM_HI))
    {
        valHigh = valHigh - LED_SEG_ASCII_OFFSET;
        valHex = LED_7SegASCII[valHigh][valLow];
    }
    else
    {
        valHex = LED_CLEAR;
    }
    
    return(valHex);
}


/*******************************************************************************
* Function Name: LED_EncodeNumber14Seg
********************************************************************************
*
* Summary:
*  Converts the lower 4 bits of the input into 14-segment data that will 
*  display the number in hex on a display. 14-segment display RAM is split into 
*  two sections (one for the lower 8 segments, one for the top 6), so the 
*  returned data must be separated into high and low bytes before being written
*  directly into the display RAM to display the desired number. It is not 
*  necessary to use this function since higher level API are provided to both 
*  decode the value and write it to the display RAM.
*
* Parameters:
*  uint8 number A number between 0x0 and 0xF to be converted into segment data.
*
* Return:
*  The value to be written into the display RAM for displaying the specific
*  number.
*
* Side effects:
*  None
*
*******************************************************************************/
uint16 LED_EncodeNumber14Seg(uint8 number) 
{
    #if(LED_SEG_DRIVE == LED_HIGH)
        /* 14-segment numerical LUT for low byte */
        static const uint8 CYCODE LED_14SegDigitsLow[16] =
              /*--------------------------------------------------------*/
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0x3fu, 0x06u, 0xdbu, 0xcfu, 0xe6u, 0xedu, 0xfdu, 0x07u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    'A'    'B'    'C'    'D'    'E'    'F'  */
              /*--------------------------------------------------------*/
                 0xffu, 0xefu, 0xf7u, 0x8fu, 0x39u, 0x0fu, 0xf9u, 0xf1u};

        /* 14-segment numerical LUT for high byte */
        static const uint8 CYCODE LED_14SegDigitsHigh[16] =
              /*--------------------------------------------------------*/
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0x24u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    'A'    'B'    'C'    'D'    'E'    'F'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x00u, 0x00u, 0x12u, 0x00u, 0x12u, 0x00u, 0x00u};
    #else
        /* 14-segment numerical LUT for low byte */
        static const uint8 CYCODE LED_14SegDigitsLow[16] =
              /*--------------------------------------------------------*/
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0xc0u, 0xf9u, 0x24u, 0x30u, 0x19u, 0x12u, 0x02u, 0xf8u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    'A'    'B'    'C'    'D'    'E'    'F'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x10u, 0x08u, 0x70u, 0xc6u, 0xf0u, 0x06u, 0x0eu};

        /* 14-segment numerical LUT for high byte */
        static const uint8 CYCODE LED_14SegDigitsHigh[16] =
              /*--------------------------------------------------------*/
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0xdbu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    'A'    'B'    'C'    'D'    'E'    'F'  */
              /*--------------------------------------------------------*/
                 0xffu, 0xffu, 0xffu, 0xedu, 0xffu, 0xedu, 0xffu, 0xffu};
    #endif /*  LED_SEG_DRIVE */
    
    uint8 valNum;
    uint16 valLow;
    uint16 valHigh;
    uint16 valHex;
    
    valNum = (uint8)(number & LED_NIBBLE_MASK);
    
    /* Get the 14-seg hex value from high and low byte LUTs */
    valHigh = (uint16)((uint16)LED_14SegDigitsHigh[valNum] << LED_SHIFT_BYTE);
    valLow = (uint16)LED_14SegDigitsLow[valNum];
    
    valHex = valHigh | valLow;
    
    return(valHex);
}


/*******************************************************************************
* Function Name: LED_EncodeChar14Seg
********************************************************************************
*
* Summary:
*  Converts the ASCII encoded alphabet character input into the 14-segment
*  data that will display the alphabet character on a display. 14-segment 
*  display RAM is split into two sections (one for the lower 8 segments, one
*  for the top 6), so the returned data must be separated into high and low 
*  bytes before being written directly into the display RAM to display the 
*  desired character. It is not necessary to use this function since higher 
*  level API are provided to both decode the value and write it to the display
*  RAM.
*
* Parameters:
*  char8 input: An ASCII alphabet character to be converted into segment data.
*
* Return:
*  The value to be written into the display RAM for displaying the specified
*  character.
*
* Side effects:
*  None
*
*******************************************************************************/
uint16 LED_EncodeChar14Seg(char8 input) 
{
    #if(LED_SEG_DRIVE == LED_HIGH)
        /* 14-segment ASCII LUT for low byte */
        static const uint8 CYCODE LED_14SegASCIILow[6][16] =
              {
              /*--------------------------------------------------------*/
              /* 'Space' '!'    '"'    '#'    '$'    '%'    '&'    '''  */
              /*--------------------------------------------------------*/
                {0x00u, 0x30u, 0x20u, 0x00u, 0x00u, 0x00u, 0x00u, 0x20u,
              /*--------------------------------------------------------*/
              /*  '('    ')'    '*'    '+'    ','    '-'    '.'    '/'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x00u, 0xc0u, 0x00u, 0x00u, 0xc0u, 0x00u, 0x00u},
              /*--------------------------------------------------------*/   
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0x3fu, 0x06u, 0xdbu, 0xcfu, 0xe6u, 0xedu, 0xfdu, 0x07u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    ':'    ';'    '<'    '='    '>'    '?'  */
              /*--------------------------------------------------------*/
                 0xffu, 0xefu, 0x00u, 0x00u, 0x00u, 0xc8u, 0x00u, 0x83u},
              /*--------------------------------------------------------*/
              /*  '@'    'A'    'B'    'C'    'D'    'E'    'F'    'G'  */
              /*--------------------------------------------------------*/
                {0x00u, 0xf7u, 0x8fu, 0x39u, 0x0fu, 0xf9u, 0xf1u, 0xbdu,
              /*--------------------------------------------------------*/
              /*  'H'    'I'    'J'    'K'    'L'    'M'    'N'    'O'  */
              /*--------------------------------------------------------*/
                 0xf6u, 0x09u, 0x1Eu, 0x70u, 0x38u, 0x36u, 0x36u, 0x3fu},
              /*--------------------------------------------------------*/
              /*  'P'    'Q'    'R'    'S'    'T'    'U'    'V'    'W'  */
              /*--------------------------------------------------------*/
                {0xf3u, 0x3fu, 0xf3u, 0xedu, 0x01u, 0x3eu, 0x30u, 0x36u,
              /*--------------------------------------------------------*/
              /*  'X'    'Y'    'Z'    '['    '\'    ']'    '^'    '_'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x00u, 0x09u, 0x00u, 0x00u, 0x00u, 0x00u, 0x08u},
              /*--------------------------------------------------------*/
              /*  '`'    'a'    'b'    'c'    'd'    'e'    'f'    'g'  */
              /*--------------------------------------------------------*/
                {0x00u, 0xf7u, 0xfcu, 0xd8u, 0xdeu, 0xf9u, 0xf1u, 0xefu,
              /*--------------------------------------------------------*/
              /*  'h'    'i'    'j'    'k'    'l'    'm'    'n'    'o'  */
              /*--------------------------------------------------------*/
                 0xf4u, 0x00u, 0x1Eu, 0x70u, 0x00u, 0xd4u, 0xd4u, 0xdcu},
              /*--------------------------------------------------------*/
              /*  'p'    'q'    'r'    's'    't'    'u'    'v'    'w'  */
              /*--------------------------------------------------------*/
                {0xf3u, 0x3fu, 0xd0u, 0xedu, 0xc0u, 0x1cu, 0x10u, 0x1cu,
              /*--------------------------------------------------------*/
              /*  'x'    'y'    'z'    '{'    '|'    '}'    '~'   'DEL' */
              /*--------------------------------------------------------*/
                 0x00u, 0x00u, 0x09u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u}
              };

        /* 14-segment ASCII LUT for high byte */
        static const uint8 CYCODE LED_14SegASCIIHigh[6][16] =
              {
              /*--------------------------------------------------------*/
              /* 'Space' '!'    '"'    '#'    '$'    '%'    '&'    '''  */
              /*--------------------------------------------------------*/
                {0x00u, 0x00u, 0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
              /*--------------------------------------------------------*/
              /*  '('    ')'    '*'    '+'    ','    '-'    '.'    '/'  */
              /*--------------------------------------------------------*/
                 0x0cu, 0x21u, 0x3fu, 0x00u, 0x20u, 0x00u, 0x00u, 0x00u},
              /*--------------------------------------------------------*/   
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0x24u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    ':'    ';'    '<'    '='    '>'    '?'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x10u},
              /*--------------------------------------------------------*/
              /*  '@'    'A'    'B'    'C'    'D'    'E'    'F'    'G'  */
              /*--------------------------------------------------------*/
                {0x00u, 0x00u, 0x12u, 0x00u, 0x12u, 0x00u, 0x00u, 0x00u,
              /*--------------------------------------------------------*/
              /*  'H'    'I'    'J'    'K'    'L'    'M'    'N'    'O'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x12u, 0x00u, 0x0cu, 0x00u, 0x05u, 0x09u, 0x00u},
              /*--------------------------------------------------------*/
              /*  'P'    'Q'    'R'    'S'    'T'    'U'    'V'    'W'  */
              /*--------------------------------------------------------*/
                {0x00u, 0x08u, 0x08u, 0x00u, 0x12u, 0x00u, 0x24u, 0x28u,
              /*--------------------------------------------------------*/
              /*  'X'    'Y'    'Z'    '['    '\'    ']'    '^'    '_'  */
              /*--------------------------------------------------------*/
                 0x2du, 0x15u, 0x24u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u},
              /*--------------------------------------------------------*/
              /*  '`'    'a'    'b'    'c'    'd'    'e'    'f'    'g'  */
              /*--------------------------------------------------------*/
                {0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
              /*--------------------------------------------------------*/
              /*  'h'    'i'    'j'    'k'    'l'    'm'    'n'    'o'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x10u, 0x00u, 0x0cu, 0x12u, 0x10u, 0x00u, 0x00u},
              /*--------------------------------------------------------*/
              /*  'p'    'q'    'r'    's'    't'    'u'    'v'    'w'  */
              /*--------------------------------------------------------*/
                {0x00u, 0x08u, 0x00u, 0x00u, 0x12u, 0x00u, 0x20u, 0x10u,
              /*--------------------------------------------------------*/
              /*  'x'    'y'    'z'    '{'    '|'    '}'    '~'   'DEL' */
              /*--------------------------------------------------------*/
                 0x2du, 0x15u, 0x24u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u}
              };
    #else
        /* 14-segment ASCII LUT for low byte */
        static const uint8 CYCODE LED_14SegASCIILow[6][16] =
              {
              /*--------------------------------------------------------*/
              /* 'Space' '!'    '"'    '#'    '$'    '%'    '&'    '''  */
              /*--------------------------------------------------------*/
                {0xffu, 0xcfu, 0xdfu, 0xffu, 0xffu, 0xffu, 0xffu, 0xdfu,
              /*--------------------------------------------------------*/
              /*  '('    ')'    '*'    '+'    ','    '-'    '.'    '/'  */
              /*--------------------------------------------------------*/
                 0xffu, 0xffu, 0x3fu, 0xffu, 0xffu, 0x3fu, 0xffu, 0xffu},
              /*--------------------------------------------------------*/   
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0xc0u, 0xf9u, 0x24u, 0x30u, 0x19u, 0x12u, 0x02u, 0xf8u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    ':'    ';'    '<'    '='    '>'    '?'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x10u, 0xffu, 0xffu, 0xffu, 0x37u, 0xffu, 0x7cu},
              /*--------------------------------------------------------*/
              /*  '@'    'A'    'B'    'C'    'D'    'E'    'F'    'G'  */
              /*--------------------------------------------------------*/
                {0xffu, 0x08u, 0x70u, 0xc6u, 0xf0u, 0x06u, 0x0eu, 0x42u,
              /*--------------------------------------------------------*/
              /*  'H'    'I'    'J'    'K'    'L'    'M'    'N'    'O'  */
              /*--------------------------------------------------------*/
                 0x09u, 0xf6u, 0xe1u, 0x8fu, 0xc7u, 0xc9u, 0xc9u, 0xc0u},
              /*--------------------------------------------------------*/
              /*  'P'    'Q'    'R'    'S'    'T'    'U'    'V'    'W'  */
              /*--------------------------------------------------------*/
                {0x0cu, 0xc0u, 0x0cu, 0x12u, 0xfeu, 0xc1u, 0xcfu, 0xc9u,
              /*--------------------------------------------------------*/
              /*  'X'    'Y'    'Z'    '['    '\'    ']'    '^'    '_'  */
              /*--------------------------------------------------------*/
                 0xffu, 0xffu, 0xf6u, 0xffu, 0xffu, 0xffu, 0xffu, 0xf7u},
              /*--------------------------------------------------------*/
              /*  '`'    'a'    'b'    'c'    'd'    'e'    'f'    'g'  */
              /*--------------------------------------------------------*/
                {0xffu, 0x08u, 0x03u, 0x27u, 0x21u, 0x06u, 0x0eu, 0x10u,
              /*--------------------------------------------------------*/
              /*  'h'    'i'    'j'    'k'    'l'    'm'    'n'    'o'  */
              /*--------------------------------------------------------*/
                 0x0bu, 0xffu, 0xe1u, 0x8fu, 0xffu, 0x2bu, 0x2bu, 0x23u},
              /*--------------------------------------------------------*/
              /*  'p'    'q'    'r'    's'    't'    'u'    'v'    'w'  */
              /*--------------------------------------------------------*/
                {0x0cu, 0xc0u, 0x2fu, 0x12u, 0x3fu, 0xe3u, 0xefu, 0xe3u,
              /*--------------------------------------------------------*/
              /*  'x'    'y'    'z'    '{'    '|'    '}'    '~'   'DEL' */
              /*--------------------------------------------------------*/
                 0xffu, 0xffu, 0xf6u, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu}
              };

        /* 14-segment ASCII LUT for high byte */
        static const uint8 CYCODE LED_14SegASCIIHigh[6][16] =
              {
              /*--------------------------------------------------------*/
              /* 'Space' '!'    '"'    '#'    '$'    '%'    '&'    '''  */
              /*--------------------------------------------------------*/
                {0xffu, 0xffu, 0xfdu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
              /*--------------------------------------------------------*/
              /*  '('    ')'    '*'    '+'    ','    '-'    '.'    '/'  */
              /*--------------------------------------------------------*/
                 0xf3u, 0xdeu, 0xc0u, 0xffu, 0xdfu, 0xffu, 0xffu, 0xffu},
              /*--------------------------------------------------------*/   
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0xdbu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    ':'    ';'    '<'    '='    '>'    '?'  */
              /*--------------------------------------------------------*/
                 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xefu},
              /*--------------------------------------------------------*/
              /*  '@'    'A'    'B'    'C'    'D'    'E'    'F'    'G'  */
              /*--------------------------------------------------------*/
                {0xffu, 0xffu, 0xedu, 0xffu, 0xedu, 0xffu, 0xffu, 0xffu,
              /*--------------------------------------------------------*/
              /*  'H'    'I'    'J'    'K'    'L'    'M'    'N'    'O'  */
              /*--------------------------------------------------------*/
                 0xffu, 0xedu, 0xffu, 0xf3u, 0xffu, 0xfau, 0xf6u, 0xffu},
              /*--------------------------------------------------------*/
              /*  'P'    'Q'    'R'    'S'    'T'    'U'    'V'    'W'  */
              /*--------------------------------------------------------*/
                {0xffu, 0xf7u, 0xf7u, 0xffu, 0xedu, 0xffu, 0xdbu, 0xd7u,
              /*--------------------------------------------------------*/
              /*  'X'    'Y'    'Z'    '['    '\'    ']'    '^'    '_'  */
              /*--------------------------------------------------------*/
                 0xd2u, 0xeau, 0xdbu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu},
              /*--------------------------------------------------------*/
              /*  '`'    'a'    'b'    'c'    'd'    'e'    'f'    'g'  */
              /*--------------------------------------------------------*/
                {0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
              /*--------------------------------------------------------*/
              /*  'h'    'i'    'j'    'k'    'l'    'm'    'n'    'o'  */
              /*--------------------------------------------------------*/
                 0xffu, 0xefu, 0xffu, 0xf3u, 0xedu, 0xefu, 0xffu, 0xffu},
              /*--------------------------------------------------------*/
              /*  'p'    'q'    'r'    's'    't'    'u'    'v'    'w'  */
              /*--------------------------------------------------------*/
                {0xffu, 0xf7u, 0xffu, 0xffu, 0xedu, 0xffu, 0xdfu, 0xefu,
              /*--------------------------------------------------------*/
              /*  'x'    'y'    'z'    '{'    '|'    '}'    '~'   'DEL' */
              /*--------------------------------------------------------*/
                 0xd2u, 0xeau, 0xdbu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu}
              };
    #endif /*  LED_SEG_DRIVE */
    
    uint8 valLow;
    uint8 valHigh;
    uint16 valHexLow;
    uint16 valHexHigh;
    uint16 valHex;
    
    valLow = (uint8)((uint8)input & LED_NIBBLE_MASK);
    
    /* valHigh used to access the row of LUT */
    valHigh = (uint8)((uint8)input >> LED_SHIFT_NIBBLE);
    
    /* Check if the high nibble is within valid ASCII range */
    if ((valHigh > LED_SEG_ASCII_LIM_LO) && (valHigh < LED_SEG_ASCII_LIM_HI))
    {
        valHigh = valHigh - LED_SEG_ASCII_OFFSET;
        
        /* Get the 14-seg hex value from high and low byte LUTs */
        valHexHigh = (uint16)((uint16)LED_14SegASCIIHigh[valHigh][valLow] << LED_SHIFT_BYTE);
        valHexLow = (uint16)LED_14SegASCIILow[valHigh][valLow];
        
        valHex = valHexHigh | valHexLow;
    }
    else
    {
        valHex = LED_CLEAR_16;
    }
        
    return(valHex);
}


/*******************************************************************************
* Function Name: LED_EncodeNumber16Seg
********************************************************************************
*
* Summary:
*  Converts the lower 4 bits of the input into 16-segment data that will 
*  display the number in hex on a display. 16-segment display RAM is split into
*  two sections for each of the eight segments, so the returned data must be 
*  separated into high and low bytes before being written directly into the
*  display RAM to display the desired number. It is not necessary to use this
*  function since higher level API are provided to both decode the value and 
*  write it to the display RAM.
*
* Parameters:
*  uint8 number: A number between 0x0 and 0xF to be converted into segment data.
*
* Return:
*  The value to be written into the display RAM for displaying the specified
*  character.
*
* Side effects:
*  None
*
*******************************************************************************/
uint16 LED_EncodeNumber16Seg(uint8 number) 
{
    #if(LED_SEG_DRIVE == LED_HIGH)
        /* 16-segment numerical LUT for low byte */
        static const uint8 CYCODE LED_16SegDigitsLow[16] =
              /*--------------------------------------------------------*/
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0xffu, 0x0cu, 0x77u, 0x3fu, 0x8cu, 0xbbu, 0xfbu, 0x0fu,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    'A'    'B'    'C'    'D'    'E'    'F'  */
              /*--------------------------------------------------------*/
                 0xffu, 0x8fu, 0xcfu, 0x3fu, 0xf3u, 0x3fu, 0xf3u, 0xc3u};

        /* 16-segment numerical LUT for high byte */
        static const uint8 CYCODE LED_16SegDigitsHigh[16] =
              /*--------------------------------------------------------*/
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0x90u, 0x00u, 0x03u, 0x03u, 0x03u, 0x03u, 0x03u, 0x00u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    'A'    'B'    'C'    'D'    'E'    'F'  */
              /*--------------------------------------------------------*/
                 0x03u, 0x03u, 0x03u, 0x4au, 0x00u, 0x48u, 0x03u, 0x03u};
    #else
        /* 16-segment numerical LUT for low byte */
        static const uint8 CYCODE LED_16SegDigitsLow[16] =
              /*--------------------------------------------------------*/
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0x00u, 0xf3u, 0x88u, 0xc0u, 0x73u, 0x44u, 0x04u, 0xf0u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    'A'    'B'    'C'    'D'    'E'    'F'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x70u, 0x30u, 0xc0u, 0x0cu, 0xc0u, 0x0cu, 0x3cu};

        /* 16-segment numerical LUT for high byte */
        static const uint8 CYCODE LED_16SegDigitsHigh[16] =
              /*--------------------------------------------------------*/
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0x6fu, 0xffu, 0xfcu, 0xfcu, 0xfcu, 0xfcu, 0xfcu, 0xffu,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    'A'    'B'    'C'    'D'    'E'    'F'  */
              /*--------------------------------------------------------*/
                 0xfcu, 0xfcu, 0xfcu, 0xb5u, 0xffu, 0xb7u, 0xfcu, 0xfcu};
    #endif /*  LED_SEG_DRIVE */
    
    uint8 valNum;
    uint16 valLow;
    uint16 valHigh;
    uint16 valHex;
    
    valNum = (uint8)(number & LED_NIBBLE_MASK);
    
    /* Get the 16-seg hex value from high and low byte LUTs */
    valHigh = (uint16)((uint16)LED_16SegDigitsHigh[valNum] << LED_SHIFT_BYTE);
    valLow = (uint16)LED_16SegDigitsLow[valNum];
    
    valHex = valHigh | valLow;
    
    return(valHex);
}


/*******************************************************************************
* Function Name: LED_EncodeChar16Seg
********************************************************************************
*
* Summary:
*  Converts the ASCII encoded alphabet character input into the 16-segment
*  data that will display the alphabet character on a display. 16-segment 
*  display RAM is split into two sections for each of the eight segments, so 
*  the returned data must be separated into high and low bytes before being 
*  written directly into the display RAM to display the desired character. It
*  is not necessary to use this function since higher level API are provided 
*  to both decode the value and write it to the display RAM.
*
* Parameters:
*  char8 input: An ASCII alphabet character to be converted into segment data.
*
* Return:
*  The value to be written into the display RAM for displaying the specified
*  character.
*
* Side effects:
*  None
*
*******************************************************************************/
uint16 LED_EncodeChar16Seg(char8 input) 
{
    #if(LED_SEG_DRIVE == LED_HIGH)
        /* 16-segment ASCII LUT for low byte */
        static const uint8 CYCODE LED_16SegASCIILow[6][16] =
              {
              /*--------------------------------------------------------*/
              /* 'Space' '!'    '"'    '#'    '$'    '%'    '&'    '''  */
              /*--------------------------------------------------------*/
                {0x00u, 0xc0u, 0x80u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u,
              /*--------------------------------------------------------*/
              /*  '('    ')'    '*'    '+'    ','    '-'    '.'    '/'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u},
              /*--------------------------------------------------------*/   
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0xffu, 0x0cu, 0x77u, 0x3fu, 0x8cu, 0xbbu, 0xfbu, 0x0fu,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    ':'    ';'    '<'    '='    '>'    '?'  */
              /*--------------------------------------------------------*/
                 0xffu, 0x8fu, 0x00u, 0x00u, 0x00u, 0x30u, 0x00u, 0x07u},
              /*--------------------------------------------------------*/
              /*  '@'    'A'    'B'    'C'    'D'    'E'    'F'    'G'  */
              /*--------------------------------------------------------*/
                {0x00u, 0xcfu, 0x3fu, 0xf3u, 0x3fu, 0xf3u, 0xc3u, 0xfbu,
              /*--------------------------------------------------------*/
              /*  'H'    'I'    'J'    'K'    'L'    'M'    'N'    'O'  */
              /*--------------------------------------------------------*/
                 0xccu, 0x33u, 0x7cu, 0xc0u, 0xf0u, 0xccu, 0xccu, 0xffu},
              /*--------------------------------------------------------*/
              /*  'P'    'Q'    'R'    'S'    'T'    'U'    'V'    'W'  */
              /*--------------------------------------------------------*/
                {0xc7u, 0xffu, 0xc7u, 0xbbu, 0x03u, 0xfcu, 0xc0u, 0xccu,
              /*--------------------------------------------------------*/
              /*  'X'    'Y'    'Z'    '['    '\'    ']'    '^'    '_'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x00u, 0x33u, 0x00u, 0x00u, 0x00u, 0x00u, 0x30u},
              /*--------------------------------------------------------*/
              /*  '`'    'a'    'b'    'c'    'd'    'e'    'f'    'g'  */
              /*--------------------------------------------------------*/
                {0x00u, 0x70u, 0xe0u, 0x60u, 0x60u, 0x60u, 0x02u, 0xa1u,
              /*--------------------------------------------------------*/
              /*  'h'    'i'    'j'    'k'    'l'    'm'    'n'    'o'  */
              /*--------------------------------------------------------*/
                 0xc0u, 0x00u, 0x20u, 0x00u, 0x00u, 0x48u, 0x08u, 0x60u},
              /*--------------------------------------------------------*/
              /*  'p'    'q'    'r'    's'    't'    'u'    'v'    'w'  */
              /*--------------------------------------------------------*/
                {0xc1u, 0x91u, 0x00u, 0x10u, 0x00u, 0x70u, 0x40u, 0x78u,
              /*--------------------------------------------------------*/
              /*  'x'    'y'    'z'    '{'    '|'    '}'    '~'   'DEL' */
              /*--------------------------------------------------------*/
                 0x00u, 0xa0u, 0x20u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u}
              };

        /* 16-segment ASCII LUT for high byte */
        static const uint8 CYCODE LED_16SegASCIIHigh[6][16] =
              {
              /*--------------------------------------------------------*/
              /* 'Space' '!'    '"'    '#'    '$'    '%'    '&'    '''  */
              /*--------------------------------------------------------*/
                {0x00u, 0x00u, 0x08u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
              /*--------------------------------------------------------*/
              /*  '('    ')'    '*'    '+'    ','    '-'    '.'    '/'  */
              /*--------------------------------------------------------*/
                 0x30u, 0x84u, 0xffu, 0x00u, 0x80u, 0x03u, 0x00u, 0x00u},
              /*--------------------------------------------------------*/   
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0x90u, 0x00u, 0x03u, 0x03u, 0x03u, 0x03u, 0x03u, 0x00u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    ':'    ';'    '<'    '='    '>'    '?'  */
              /*--------------------------------------------------------*/
                 0x03u, 0x03u, 0x00u, 0x00u, 0x00u, 0x03u, 0x00u, 0x42u},
              /*--------------------------------------------------------*/
              /*  '@'    'A'    'B'    'C'    'D'    'E'    'F'    'G'  */
              /*--------------------------------------------------------*/
                {0x00u, 0x03u, 0x4au, 0x00u, 0x48u, 0x03u, 0x03u, 0x02u,
              /*--------------------------------------------------------*/
              /*  'H'    'I'    'J'    'K'    'L'    'M'    'N'    'O'  */
              /*--------------------------------------------------------*/
                 0x03u, 0x48u, 0x00u, 0x31u, 0x00u, 0x14u, 0x24u, 0x00u},
              /*--------------------------------------------------------*/
              /*  'P'    'Q'    'R'    'S'    'T'    'U'    'V'    'W'  */
              /*--------------------------------------------------------*/
                {0x03u, 0x20u, 0x23u, 0x03u, 0x48u, 0x00u, 0x90u, 0xa0u,
              /*--------------------------------------------------------*/
              /*  'X'    'Y'    'Z'    '['    '\'    ']'    '^'    '_'  */
              /*--------------------------------------------------------*/
                 0xb4u, 0x54u, 0x90u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u},
              /*--------------------------------------------------------*/
              /*  '`'    'a'    'b'    'c'    'd'    'e'    'f'    'g'  */
              /*--------------------------------------------------------*/
                {0x00u, 0x41u, 0x41u, 0x01u, 0x49u, 0x81u, 0x4bu, 0x49u,
              /*--------------------------------------------------------*/
              /*  'h'    'i'    'j'    'k'    'l'    'm'    'n'    'o'  */
              /*--------------------------------------------------------*/
                 0x41u, 0x40u, 0x48u, 0x6au, 0x48u, 0x43u, 0x43u, 0x41u},
              /*--------------------------------------------------------*/
              /*  'p'    'q'    'r'    's'    't'    'u'    'v'    'w'  */
              /*--------------------------------------------------------*/
                {0x09u, 0x49u, 0x42u, 0x22u, 0x4bu, 0x40u, 0x80u, 0x40u,
              /*--------------------------------------------------------*/
              /*  'x'    'y'    'z'    '{'    '|'    '}'    '~'   'DEL' */
              /*--------------------------------------------------------*/
                 0xb4u, 0x49u, 0x81u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u}
              };
    #else
        /* 16-segment ASCII LUT for low byte */
        static const uint8 CYCODE LED_16SegASCIILow[6][16] =
              {
              /*--------------------------------------------------------*/
              /* 'Space' '!'    '"'    '#'    '$'    '%'    '&'    '''  */
              /*--------------------------------------------------------*/
                {0xffu, 0x3fu, 0x7fu, 0xffu, 0xffu, 0xffu, 0xffu, 0x7fu,
              /*--------------------------------------------------------*/
              /*  '('    ')'    '*'    '+'    ','    '-'    '.'    '/'  */
              /*--------------------------------------------------------*/
                 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu},
              /*--------------------------------------------------------*/   
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0x00u, 0xf3u, 0x88u, 0xc0u, 0x73u, 0x44u, 0x04u, 0xf0u,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    ':'    ';'    '<'    '='    '>'    '?'  */
              /*--------------------------------------------------------*/
                 0x00u, 0x70u, 0xffu, 0xffu, 0xffu, 0xcfu, 0xffu, 0xf8u},
              /*--------------------------------------------------------*/
              /*  '@'    'A'    'B'    'C'    'D'    'E'    'F'    'G'  */
              /*--------------------------------------------------------*/
                {0xffu, 0x30u, 0xc0u, 0x0cu, 0xc0u, 0x0cu, 0x3cu, 0x04u,
              /*--------------------------------------------------------*/
              /*  'H'    'I'    'J'    'K'    'L'    'M'    'N'    'O'  */
              /*--------------------------------------------------------*/
                 0x33u, 0xccu, 0x83u, 0x3fu, 0x0fu, 0x33u, 0x33u, 0x00u},
              /*--------------------------------------------------------*/
              /*  'P'    'Q'    'R'    'S'    'T'    'U'    'V'    'W'  */
              /*--------------------------------------------------------*/
                {0x38u, 0x00u, 0x38u, 0x44u, 0xfcu, 0x03u, 0x3fu, 0x33u,
              /*--------------------------------------------------------*/
              /*  'X'    'Y'    'Z'    '['    '\'    ']'    '^'    '_'  */
              /*--------------------------------------------------------*/
                 0xffu, 0xffu, 0xccu, 0xffu, 0xffu, 0xffu, 0xffu, 0xcfu},
              /*--------------------------------------------------------*/
              /*  '`'    'a'    'b'    'c'    'd'    'e'    'f'    'g'  */
              /*--------------------------------------------------------*/
                {0xffu, 0x8fu, 0x1fu, 0x9fu, 0x9fu, 0x9fu, 0xfdu, 0x5eu,
              /*--------------------------------------------------------*/
              /*  'h'    'i'    'j'    'k'    'l'    'm'    'n'    'o'  */
              /*--------------------------------------------------------*/
                 0x3fu, 0xffu, 0xdfu, 0xffu, 0xffu, 0xb7u, 0xf7u, 0x9fu},
              /*--------------------------------------------------------*/
              /*  'p'    'q'    'r'    's'    't'    'u'    'v'    'w'  */
              /*--------------------------------------------------------*/
                {0x3eu, 0x6eu, 0xffu, 0xefu, 0xffu, 0x8fu, 0xbfu, 0x87u,
              /*--------------------------------------------------------*/
              /*  'x'    'y'    'z'    '{'    '|'    '}'    '~'   'DEL' */
              /*--------------------------------------------------------*/
                 0xffu, 0x5fu, 0xdfu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu}
              };

        /* 16-segment ASCII LUT for high byte */
        static const uint8 CYCODE LED_16SegASCIIHigh[6][16] =
              {
              /*--------------------------------------------------------*/
              /* 'Space' '!'    '"'    '#'    '$'    '%'    '&'    '''  */
              /*--------------------------------------------------------*/
                {0xffu, 0xffu, 0xf7u, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
              /*--------------------------------------------------------*/
              /*  '('    ')'    '*'    '+'    ','    '-'    '.'    '/'  */
              /*--------------------------------------------------------*/
                 0xcfu, 0x7bu, 0x00u, 0xffu, 0x7fu, 0xfcu, 0xffu, 0xffu},
              /*--------------------------------------------------------*/   
              /*  '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7'  */
              /*--------------------------------------------------------*/
                {0x6fu, 0xffu, 0xfcu, 0xfcu, 0xfcu, 0xfcu, 0xfcu, 0xffu,
              /*--------------------------------------------------------*/
              /*  '8'    '9'    ':'    ';'    '<'    '='    '>'    '?'  */
              /*--------------------------------------------------------*/
                 0xfcu, 0xfcu, 0xffu, 0xffu, 0xffu, 0xfcu, 0xffu, 0xbdu},
              /*--------------------------------------------------------*/
              /*  '@'    'A'    'B'    'C'    'D'    'E'    'F'    'G'  */
              /*--------------------------------------------------------*/
                {0xffu, 0xfcu, 0xb5u, 0xffu, 0xb7u, 0xfcu, 0xfcu, 0xfdu,
              /*--------------------------------------------------------*/
              /*  'H'    'I'    'J'    'K'    'L'    'M'    'N'    'O'  */
              /*--------------------------------------------------------*/
                 0xfcu, 0xb7u, 0xffu, 0xceu, 0xffu, 0xebu, 0xdbu, 0xffu},
              /*--------------------------------------------------------*/
              /*  'P'    'Q'    'R'    'S'    'T'    'U'    'V'    'W'  */
              /*--------------------------------------------------------*/
                {0xfcu, 0xdfu, 0xdcu, 0xfcu, 0xb7u, 0xffu, 0x6fu, 0x5fu,
              /*--------------------------------------------------------*/
              /*  'X'    'Y'    'Z'    '['    '\'    ']'    '^'    '_'  */
              /*--------------------------------------------------------*/
                 0x4bu, 0xabu, 0x6fu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu},
              /*--------------------------------------------------------*/
              /*  '`'    'a'    'b'    'c'    'd'    'e'    'f'    'g'  */
              /*--------------------------------------------------------*/
                {0xffu, 0xbeu, 0xbeu, 0xfeu, 0xb6u, 0x7eu, 0xb4u, 0xb6u,
              /*--------------------------------------------------------*/
              /*  'h'    'i'    'j'    'k'    'l'    'm'    'n'    'o'  */
              /*--------------------------------------------------------*/
                 0xbeu, 0xbfu, 0xb7u, 0x95u, 0xb7u, 0xbcu, 0xbcu, 0xbeu},
              /*--------------------------------------------------------*/
              /*  'p'    'q'    'r'    's'    't'    'u'    'v'    'w'  */
              /*--------------------------------------------------------*/
                {0xf6u, 0xb6u, 0xbdu, 0xddu, 0xb4u, 0xbfu, 0x7fu, 0xbfu,
              /*--------------------------------------------------------*/
              /*  'x'    'y'    'z'    '{'    '|'    '}'    '~'   'DEL' */
              /*--------------------------------------------------------*/
                 0x4bu, 0xb6u, 0x7eu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu}
              };
    #endif /*  LED_SEG_DRIVE */
    
    uint8 valLow;
    uint8 valHigh;
    uint16 valHexLow;
    uint16 valHexHigh;
    uint16 valHex;
    
    valLow = (uint8)((uint8)input & LED_NIBBLE_MASK);
    
    /* valHigh used to access the row of LUT */
    valHigh = (uint8)((uint8)input >> LED_SHIFT_NIBBLE);
    
    /* Check if the high nibble is within valid ASCII range */
    if ((valHigh > LED_SEG_ASCII_LIM_LO) && (valHigh < LED_SEG_ASCII_LIM_HI))
    {
        valHigh = valHigh - LED_SEG_ASCII_OFFSET;
        
        /* Get the 16-seg hex value from high and low byte LUTs */
        valHexHigh = (uint16)((uint16)LED_16SegASCIIHigh[valHigh][valLow] << LED_SHIFT_BYTE);
        valHexLow = (uint16)LED_16SegASCIILow[valHigh][valLow];
        
        valHex = valHexHigh | valHexLow;
    }
    else
    {
        valHex = LED_CLEAR_16;
    }
        
    return(valHex);
}


#if (LED_BRIGHTNESS_EN == LED_ENABLED)


/*******************************************************************************
* Function Name: LED_SetBrightness
********************************************************************************
*
* Summary:
*  Sets the desired brightness value (0 = display off; 255 = display at full
*  brightness) for the chosen display by applying a PWM duty cycle to that
*  displays common when the display is active.
*
* Parameters:
*  uint8 bright: The brightness value by duty cycle, between 1 and 255.
*  uint8 position: The position in which to set the brightness.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void LED_SetBrightness(uint8 bright, uint8 position)

{   
    #if(LED_COM_DRIVE == LED_HIGH)
        static const uint8 CYCODE LED_tempCom[16] = {0x00u, 0x01u, 0x00u, 0x02u, 0x00u, 0x04u,
                                                                  0x00u, 0x08u, 0x00u, 0x10u, 0x00u, 0x20u,
                                                                  0x00u, 0x40u, 0x00u, 0x80u};
    #else
        static const uint8 CYCODE LED_tempCom[16] = {0xFFu, 0xFEu, 0xFFu, 0xFDu, 0xFFu, 0xFBu,
                                                                  0xFFu, 0xF7u, 0xFFu, 0xEFu, 0xFFu, 0xDFu,
                                                                  0xFFu, 0xBFu, 0xFFu, 0x7Fu};
    #endif /* (LED_COM_DRIVE == LED_HIGH) */
    
    if(bright == 0u)
    {
        /* Turn off the commons */
        LED_comBuffer[(uint8)((uint8)position << 1u) + 1u] = LED_CLEAR;
    }
    else
    {
        /* Restore the commons */
        LED_comBuffer[(uint8)((uint8)position << 1u) + 1u]
            = LED_tempCom[(uint8)((uint8)position << 1u) + 1u];
    }
    
    /* Update the brightness register */
    LED_brightnessReg[position] = bright;
}


/*******************************************************************************
* Function Name: LED_GetBrightness
********************************************************************************
*
* Summary:
*  Returns the brightness value for the specific display location.
*
* Parameters:
*  uint8 position: Position in which to return the brightness value.
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
uint8 LED_GetBrightness(uint8 position) 
{
    return(LED_brightnessReg[position]);
}

#endif /*  (LED_BRIGHTNESS_EN == LED_ENABLED) */

/* [] END OF FILE */

