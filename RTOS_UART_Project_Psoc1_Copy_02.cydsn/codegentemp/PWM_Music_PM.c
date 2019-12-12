/*******************************************************************************
* File Name: PWM_Music_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_Music.h"

static PWM_Music_backupStruct PWM_Music_backup;


/*******************************************************************************
* Function Name: PWM_Music_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Music_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Music_SaveConfig(void) 
{

    #if(!PWM_Music_UsingFixedFunction)
        #if(!PWM_Music_PWMModeIsCenterAligned)
            PWM_Music_backup.PWMPeriod = PWM_Music_ReadPeriod();
        #endif /* (!PWM_Music_PWMModeIsCenterAligned) */
        PWM_Music_backup.PWMUdb = PWM_Music_ReadCounter();
        #if (PWM_Music_UseStatus)
            PWM_Music_backup.InterruptMaskValue = PWM_Music_STATUS_MASK;
        #endif /* (PWM_Music_UseStatus) */

        #if(PWM_Music_DeadBandMode == PWM_Music__B_PWM__DBM_256_CLOCKS || \
            PWM_Music_DeadBandMode == PWM_Music__B_PWM__DBM_2_4_CLOCKS)
            PWM_Music_backup.PWMdeadBandValue = PWM_Music_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Music_KillModeMinTime)
             PWM_Music_backup.PWMKillCounterPeriod = PWM_Music_ReadKillTime();
        #endif /* (PWM_Music_KillModeMinTime) */

        #if(PWM_Music_UseControl)
            PWM_Music_backup.PWMControlRegister = PWM_Music_ReadControlRegister();
        #endif /* (PWM_Music_UseControl) */
    #endif  /* (!PWM_Music_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Music_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Music_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Music_RestoreConfig(void) 
{
        #if(!PWM_Music_UsingFixedFunction)
            #if(!PWM_Music_PWMModeIsCenterAligned)
                PWM_Music_WritePeriod(PWM_Music_backup.PWMPeriod);
            #endif /* (!PWM_Music_PWMModeIsCenterAligned) */

            PWM_Music_WriteCounter(PWM_Music_backup.PWMUdb);

            #if (PWM_Music_UseStatus)
                PWM_Music_STATUS_MASK = PWM_Music_backup.InterruptMaskValue;
            #endif /* (PWM_Music_UseStatus) */

            #if(PWM_Music_DeadBandMode == PWM_Music__B_PWM__DBM_256_CLOCKS || \
                PWM_Music_DeadBandMode == PWM_Music__B_PWM__DBM_2_4_CLOCKS)
                PWM_Music_WriteDeadTime(PWM_Music_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Music_KillModeMinTime)
                PWM_Music_WriteKillTime(PWM_Music_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Music_KillModeMinTime) */

            #if(PWM_Music_UseControl)
                PWM_Music_WriteControlRegister(PWM_Music_backup.PWMControlRegister);
            #endif /* (PWM_Music_UseControl) */
        #endif  /* (!PWM_Music_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Music_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Music_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Music_Sleep(void) 
{
    #if(PWM_Music_UseControl)
        if(PWM_Music_CTRL_ENABLE == (PWM_Music_CONTROL & PWM_Music_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Music_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Music_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Music_UseControl) */

    /* Stop component */
    PWM_Music_Stop();

    /* Save registers configuration */
    PWM_Music_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Music_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Music_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Music_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Music_RestoreConfig();

    if(PWM_Music_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Music_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
