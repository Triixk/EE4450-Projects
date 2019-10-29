/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(void)
{
    bool proximity;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CapSense_Start();
    CapSense_EnableWidget(0);
    CapSense_InitializeAllBaselines();
    
    for(;;)
    {
        /* Place your application code here. */
        CapSense_UpdateEnabledBaselines();
        proximity = CapSense_CheckIsWidgetActive(0);
        LED_Write(proximity);
        CapSense_ScanEnabledWidgets();
    }
}

/* [] END OF FILE */
