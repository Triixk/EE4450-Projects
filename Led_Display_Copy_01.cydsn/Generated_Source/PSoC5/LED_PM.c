/*******************************************************************************
* File Name: LED_PM.c
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

#include "LED.h"
static LED_backupStruct LED_backup;


/*******************************************************************************
* Function Name: LED_Sleep
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
void LED_Sleep(void) 
{
    uint8 i;
    
    /* Store the component enable state */
    LED_backup.ledEnableState = LED_enableVar;
    
    /* Save the segment buffers */
    for(i = 0u; i < LED_NUM_COM; i++)
    {
        LED_backup.segLBackup[i] = LED_segLBuffer[i];
        #if (LED_NUM_SEG > 8u) 
            LED_backup.segMBackup[i] = LED_segMBuffer[i];
        #endif /* (LED_NUM_SEG > 8u) */
        #if (LED_NUM_SEG > 16u) 
            LED_backup.segHBackup[i] = LED_segHBuffer[i];
        #endif /* (LED_NUM_SEG > 16u) */
    }
    
    LED_Stop();
}


/*******************************************************************************
* Function Name: LED_Wakeup
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
void LED_Wakeup(void) 
{
    uint8 i;
    
    /* Restore the segment buffers */
    for(i = 0u; i < LED_NUM_COM; i++)
    {
        LED_segLBuffer[i] = LED_backup.segLBackup[i];
        #if (LED_NUM_SEG > 8u) 
            LED_segMBuffer[i] = LED_backup.segMBackup[i];
        #endif /* (LED_NUM_SEG > 8u) */
        #if (LED_NUM_SEG > 16u) 
            LED_segHBuffer[i] = LED_backup.segHBackup[i];
        #endif /* (LED_NUM_SEG > 16u) */
    }
    
    if(LED_backup.ledEnableState == LED_ENABLED)
    {
        /* Enable the component */
        LED_Enable();
    }
}


/* [] END OF FILE */

