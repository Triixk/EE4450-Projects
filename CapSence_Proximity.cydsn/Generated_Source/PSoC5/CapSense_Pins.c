/*******************************************************************************
* File Name: CapSense_Pins.c
* Version 3.50
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CapSense_Pins.h"


/*******************************************************************************
* Function Name: CapSense_SetAllSensorsDriveMode
********************************************************************************
*
* Summary:
*  Sets the drive mode for the all pins used by capacitive sensors within 
*  CapSense component.
* 
* Parameters:  
*  mode: Desired drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void CapSense_SetAllSensorsDriveMode(uint8 mode) 
{
    /* Set pins drive mode */
    CyPins_SetPinDriveMode(CapSense_PortCH0__ProximitySensor0_0__PROX, mode);

}



/*******************************************************************************
* Function Name: CapSense_SetAllCmodsDriveMode
********************************************************************************
*
* Summary:
*  Sets the drive mode for the all pins used by Cmod capacitors within CapSense 
*  component.
* 
* Parameters:  
*  mode: Desired drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void CapSense_SetAllCmodsDriveMode(uint8 mode) 
{
   /* Set pins drive mode */
    CyPins_SetPinDriveMode(CapSense_CmodCH0_Cmod_CH0, mode);

}


#if (CapSense_CURRENT_SOURCE == CapSense_EXTERNAL_RB)
    /*******************************************************************************
    * Function Name: CapSense_SetAllRbsDriveMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the drive mode for the all pins used by bleed resistors (Rb) within 
    *  CapSense component. Only available when Current Source is external resistor.
    * 
    * Parameters:  
    *  mode: Desired drive mode.
    *
    * Return: 
    *  None
    *
    *******************************************************************************/
    void CapSense_SetAllRbsDriveMode(uint8 mode) 
    {
        /* Set pins drive mode */
      
    }
#endif  /* (CapSense_CURRENT_SOURCE == CapSense_EXTERNAL_RB) */


/* [] END OF FILE */
