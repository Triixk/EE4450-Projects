/*******************************************************************************
* File Name: UARTB_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
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


/***************************************
* Local data allocation
***************************************/

static UARTB_BACKUP_STRUCT  UARTB_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: UARTB_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the UARTB_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UARTB_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UARTB_SaveConfig(void)
{
    #if(UARTB_CONTROL_REG_REMOVED == 0u)
        UARTB_backup.cr = UARTB_CONTROL_REG;
    #endif /* End UARTB_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UARTB_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UARTB_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling UARTB_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void UARTB_RestoreConfig(void)
{
    #if(UARTB_CONTROL_REG_REMOVED == 0u)
        UARTB_CONTROL_REG = UARTB_backup.cr;
    #endif /* End UARTB_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UARTB_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The UARTB_Sleep() API saves the current component state. Then it
*  calls the UARTB_Stop() function and calls 
*  UARTB_SaveConfig() to save the hardware configuration.
*  Call the UARTB_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UARTB_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UARTB_Sleep(void)
{
    #if(UARTB_RX_ENABLED || UARTB_HD_ENABLED)
        if((UARTB_RXSTATUS_ACTL_REG  & UARTB_INT_ENABLE) != 0u)
        {
            UARTB_backup.enableState = 1u;
        }
        else
        {
            UARTB_backup.enableState = 0u;
        }
    #else
        if((UARTB_TXSTATUS_ACTL_REG  & UARTB_INT_ENABLE) !=0u)
        {
            UARTB_backup.enableState = 1u;
        }
        else
        {
            UARTB_backup.enableState = 0u;
        }
    #endif /* End UARTB_RX_ENABLED || UARTB_HD_ENABLED*/

    UARTB_Stop();
    UARTB_SaveConfig();
}


/*******************************************************************************
* Function Name: UARTB_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  UARTB_Sleep() was called. The UARTB_Wakeup() function
*  calls the UARTB_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  UARTB_Sleep() function was called, the UARTB_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UARTB_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UARTB_Wakeup(void)
{
    UARTB_RestoreConfig();
    #if( (UARTB_RX_ENABLED) || (UARTB_HD_ENABLED) )
        UARTB_ClearRxBuffer();
    #endif /* End (UARTB_RX_ENABLED) || (UARTB_HD_ENABLED) */
    #if(UARTB_TX_ENABLED || UARTB_HD_ENABLED)
        UARTB_ClearTxBuffer();
    #endif /* End UARTB_TX_ENABLED || UARTB_HD_ENABLED */

    if(UARTB_backup.enableState != 0u)
    {
        UARTB_Enable();
    }
}


/* [] END OF FILE */
