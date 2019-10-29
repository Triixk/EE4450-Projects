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

#define NOFINGER 0xFFFFu

int main(void)
{
    
    uint16_t    sliderPostion   = NOFINGER;
    uint16_t    lastPostion     = NOFINGER;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    PWM_Start();
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    
    for(;;)
    {
        /* Place your application code here. */
        CapSense_UpdateEnabledBaselines();
        CapSense_ScanEnabledWidgets();
        
        while(CapSense_IsBusy());
        
        sliderPostion = CapSense_GetCentroidPos(0);
        
        if (sliderPostion != NOFINGER){
            if (sliderPostion != lastPostion){
                lastPostion = sliderPostion;
                PWM_WriteCompare(sliderPostion);
            }
        }
    }
}

/* [] END OF FILE */
