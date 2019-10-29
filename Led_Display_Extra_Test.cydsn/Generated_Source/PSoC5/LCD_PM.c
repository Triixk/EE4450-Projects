/*******************************************************************************
* File Name: LCD_PM.c
* Version 1.10
*
* Description:
*  This file provides the power management source code to API for the
*  LED_Driver component.
*
* Note:
*  None
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "LCD.h"
static LCD_backupStruct LCD_backup;


/*******************************************************************************
* Function Name: LCD_Sleep
********************************************************************************
*
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LCD_Sleep(void) 
{
    uint8 i;
    
    /* Store the component enable state */
    LCD_backup.ledEnableState = LCD_enableVar;
    
    /* Save the segment buffers */
    for(i = 0u; i < LCD_NUM_COM; i++)
    {
        LCD_backup.segLBackup[i] = LCD_segLBuffer[i];
        #if (LCD_NUM_SEG > 8u) 
            LCD_backup.segMBackup[i] = LCD_segMBuffer[i];
        #endif /* (LCD_NUM_SEG > 8u) */
        #if (LCD_NUM_SEG > 16u) 
            LCD_backup.segHBackup[i] = LCD_segHBuffer[i];
        #endif /* (LCD_NUM_SEG > 16u) */
    }
    
    LCD_Stop();
}


/*******************************************************************************
* Function Name: LCD_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LCD_Wakeup(void) 
{
    uint8 i;
    
    /* Restore the segment buffers */
    for(i = 0u; i < LCD_NUM_COM; i++)
    {
        LCD_segLBuffer[i] = LCD_backup.segLBackup[i];
        #if (LCD_NUM_SEG > 8u) 
            LCD_segMBuffer[i] = LCD_backup.segMBackup[i];
        #endif /* (LCD_NUM_SEG > 8u) */
        #if (LCD_NUM_SEG > 16u) 
            LCD_segHBuffer[i] = LCD_backup.segHBackup[i];
        #endif /* (LCD_NUM_SEG > 16u) */
    }
    
    if(LCD_backup.ledEnableState == LCD_ENABLED)
    {
        /* Enable the component */
        LCD_Enable();
    }
}


/* [] END OF FILE */

